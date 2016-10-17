// TODO: license text

#include "physicworld.hpp"

#include "box.hpp"
#include "chainshape.hpp"
#include "circle.hpp"
#include "global.hpp"
#include "map.hpp"
#include "objectlayer.hpp"
#include "physicobject.hpp"
#include "polygonshape.hpp"

#include <SFML/System/Time.hpp>

#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <iostream> // TODO: remove
#include <memory>

#include<Box2D/Box2D.h>

namespace ibrengine
{

class CollisionDetector: public b2ContactListener
{
public:
  void BeginContact(b2Contact* contact) override
  {
    PhysicObject *p1 = static_cast<PhysicObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    PhysicObject *p2 = static_cast<PhysicObject*>(contact->GetFixtureB()->GetBody()->GetUserData());
    ::std::cout << "contact begin with: " << p1->getDensity() << " and " << p2->getDensity() << ::std::endl;
  }

  void EndContact(b2Contact* contact) override
  {
    PhysicObject *p1 = static_cast<PhysicObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    PhysicObject *p2 = static_cast<PhysicObject*>(contact->GetFixtureB()->GetBody()->GetUserData());
    ::std::cout << "contact end with: " << p1->getDensity() << " and " << p2->getDensity() << ::std::endl;
  }
};

PhysicWorld::PhysicWorld(DebugDraw &dDraw):
  mWorld(b2Vec2(0.0f, 9.8f)),
  mContactListener(new CollisionDetector)
{
  mWorld.SetContactListener(mContactListener.get());
}

PhysicWorld::~PhysicWorld()
{
  for (b2Body *body: mBodies)
    mWorld.DestroyBody(body);
}

void PhysicWorld::update(const sf::Time& time)
{
  mWorld.Step(time.asSeconds(), VelocityIterations, PositionIterations);
  b2Body *bodies = mWorld.GetBodyList();
  for (b2Body *body: mBodies)
  {
    PhysicObject *physObj = static_cast<PhysicObject*>(body->GetUserData());
    if (physObj != nullptr)
      changePhysicObject(*body, *physObj);
  }
}

void PhysicWorld::initFromMap(const Map &map)
{
  for (auto i = map.layersBegin(); i != map.layersEnd(); ++i)
  {
    if (i->get()->getType() == Layer::Type::Object)
    {
      const ObjectLayer *objLayer = static_cast<ObjectLayer*>(i->get());
      for (auto i = objLayer->beginPhysicalObjs(); i != objLayer->endPhysicalObjs(); ++i)
      {
        const PhysicObject *physObj = static_cast<PhysicObject*>((*i).get());
        createBody(*physObj);
      }
    }
  }
}

void PhysicWorld::createBody(const PhysicObject &obj)
{
  b2BodyDef bodyDef;
  bodyDef.type = static_cast<b2BodyType>(obj.getType());
  bodyDef.active = obj.isActive();
  bodyDef.allowSleep = obj.isAllowSleep();
  bodyDef.angle = obj.getAngle() / DegreesPerRadian;
  bodyDef.angularDamping = obj.getAngularDamping();
  bodyDef.angularVelocity = obj.getAngularVelocity();
  bodyDef.awake = obj.isAwake();
  bodyDef.bullet = obj.isBullet();
  bodyDef.fixedRotation = obj.isFixedRotation();
  bodyDef.gravityScale = obj.getGravityScale();
  bodyDef.linearDamping = obj.getLinearDamping();
  bodyDef.linearVelocity.Set(obj.getLinearVelocity().first, obj.getLinearVelocity().second);
  bodyDef.position.Set(
    obj.getPosition().first / PixelsPerUnit,
    (obj.getPosition().second - obj.getSize().second) / PixelsPerUnit);
  b2Body *newBody = mWorld.CreateBody(&bodyDef);

  // For all shapes we create the fixtures.
  for (const std::shared_ptr<internal::Shape> &shape: obj.getShapeGroup())
  {
    if (!shape->isValid())
      continue;

    b2FixtureDef fixtureDef;
    fixtureDef.density = obj.getDensity();
    fixtureDef.friction = obj.getFriction();
    fixtureDef.isSensor = obj.isSensor();
    fixtureDef.restitution = obj.getRestitution();

    b2Shape *newShape = nullptr;
    if (shape->getType() == internal::Shape::Type::Box)
    {
      const internal::Box *box = dynamic_cast<const internal::Box*>(shape.get());
      b2PolygonShape *polygonShape = new b2PolygonShape;

      std::array<b2Vec2,4 > vertices =
      {
          b2Vec2(0.0f, 0.0f),
          b2Vec2(box->getWidth() / PixelsPerUnit, 0.0f),
          b2Vec2(box->getWidth() / PixelsPerUnit, box->getHeight() / PixelsPerUnit),
          b2Vec2(0.0f, box->getHeight() / PixelsPerUnit)
      };

      /*
       * For objects linked to tile (i.e. collision objects) we should use an offset
       * to correctly position them relative to the object's tile. There is no need to
       * do such things for free objects put on the map, because they don't use
       * tiles.
       */
      if (box->isLinkedToTile())
      {
        for (b2Vec2 &vertex: vertices)
          vertex += b2Vec2(box->getPosition().first / PixelsPerUnit, box->getPosition().second / PixelsPerUnit);
      }

      polygonShape->Set(vertices.data(), vertices.size());
      newShape = polygonShape;
    }
    else if (shape->getType() == internal::Shape::Type::Circle)
    {
      const internal::Circle *circle = dynamic_cast<const internal::Circle*>(shape.get());
      b2CircleShape *circleShape = new b2CircleShape;
      circleShape->m_radius = circle->getRadius() / PixelsPerUnit;
      circleShape->m_p += b2Vec2(circleShape->m_radius, circleShape->m_radius);
      if (circle->isLinkedToTile())
        circleShape->m_p += b2Vec2(
            circle->getPosition().first / PixelsPerUnit,
            circle->getPosition().second / PixelsPerUnit);
      newShape = circleShape;
    }
    else if (shape->getType() == internal::Shape::Type::Chain)
    {
      const internal::ChainShape *chain = dynamic_cast<const internal::ChainShape*>(shape.get());
      const size_t pointsCount = chain->getPointsCount();
      std::unique_ptr<b2Vec2[]> vertices(new b2Vec2[pointsCount]);
      for (size_t i = 0; i < pointsCount; ++i)
      {
        vertices[i].Set(chain->getPoint(i).first / PixelsPerUnit, chain->getPoint(i).second / PixelsPerUnit);
        if (chain->isLinkedToTile())
          vertices[i] += b2Vec2(chain->getPosition().first / PixelsPerUnit, chain->getPosition().second / PixelsPerUnit);
      }

      b2ChainShape *chainShape = new b2ChainShape;
      chainShape->CreateChain(vertices.get(), pointsCount);
      newShape = chainShape;
    }
    else if (shape->getType() == internal::Shape::Type::Polygon)
    {
      const internal::PolygonShape *polyShape = dynamic_cast<const internal::PolygonShape*>(shape.get());
      b2PolygonShape *polygonShape = new b2PolygonShape;
      std::unique_ptr<b2Vec2[]> vertices(new b2Vec2[polyShape->getPointsCount()]);
      auto i = polyShape->beginPoints();
      while (i != polyShape->endPoints())
      {
        vertices[i - polyShape->beginPoints()] = b2Vec2(i->first / PixelsPerUnit, i->second / PixelsPerUnit);
        if (polyShape->isLinkedToTile())
          vertices[i - polyShape->beginPoints()] += b2Vec2(polyShape->getPosition().first / PixelsPerUnit, polyShape->getPosition().second / PixelsPerUnit);
        ++i;
      }
      polygonShape->Set(vertices.get(), polyShape->getPointsCount());
      newShape = polygonShape;
    }

    if (newShape != nullptr)
    {
      fixtureDef.shape = newShape;
      b2Fixture *newFixture = newBody->CreateFixture(&fixtureDef); // TODO: Destroy on removal?
    }
    delete newShape;
  }
  newBody->SetUserData(const_cast<PhysicObject*>(&obj));
  mBodies.push_back(newBody);
}

void PhysicWorld::changePhysicObject(const b2Body &body, PhysicObject &physObj)
{
  physObj.setType(static_cast<PhysicObject::Type>(body.GetType()));
  physObj.setActive(body.IsActive());
  physObj.setAngle(body.GetAngle() * DegreesPerRadian);
  physObj.setAngularDamping(body.GetAngularDamping());
  physObj.setAngularVelocity(body.GetAngularVelocity());
  physObj.setAllowSleep(body.IsSleepingAllowed());
  physObj.setAwake(body.IsAwake());
  physObj.setBullet(body.IsBullet());
  physObj.setFixedRotation(body.IsFixedRotation());
  physObj.setGravityScale(body.GetGravityScale());
  physObj.setLinearDamping(body.GetLinearDamping());
  physObj.setLinearVelocity(LinearVelocity(body.GetLinearVelocity().x, body.GetLinearVelocity().y));
  physObj.setPosition(std::make_pair(body.GetPosition().x * PixelsPerUnit, body.GetPosition().y * PixelsPerUnit));
  physObj.setChanged();
}

} // namespace ibrengine
