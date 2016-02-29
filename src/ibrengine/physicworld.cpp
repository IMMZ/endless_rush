// TODO: license text

#include "physicworld.hpp"

#include "box.hpp"
#include "circle.hpp"
#include "global.hpp"
#include "map.hpp"
#include "objectlayer.hpp"
#include "physicobject.hpp"

#include <SFML/System/Time.hpp>

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <iostream> // TODO: remove

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

PhysicWorld::PhysicWorld():
  mWorld(b2Vec2(0.0f,-9.8f)),
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
  if (ball != nullptr)
    ::std::cout << "obj pos is: " << ball->GetPosition().x << ", " << ball->GetPosition().y << ::std::endl;
}

void PhysicWorld::initFromMap(const Map &map)
{
  b2AABB worldSize;
  worldSize.lowerBound.Set(0.0f, 0.0f);
  worldSize.upperBound.Set(map.getW(), map.getH());

  for (auto i = map.layersBegin(); i != map.layersEnd(); ++i)
  {
    if (i->get()->getType() == Layer::Type::Object)
    {
      ObjectLayer *objLayer = static_cast<ObjectLayer*>(i->get());
      for (auto obj = objLayer->beginPhysicalObjs(); obj != objLayer->endPhysicalObjs(); ++obj)
        createBody(*(*obj));
    }
  }
}

void PhysicWorld::createBody(const PhysicObject &obj)
{
  ::std::cout << "BODY CREATED" << ::std::endl;
  b2BodyDef bodyDef;
  bodyDef.type = static_cast<b2BodyType>(obj.getType());
  if (bodyDef.type == b2_staticBody)
    ::std::cout << "STATTIC";
  else if (bodyDef.type == b2_dynamicBody)
    ::std::cout << "DYNNAMIC";
  ::std::cout << ::std::endl;
  bodyDef.active = obj.isActive();
  bodyDef.allowSleep = obj.isAllowSleep();
  bodyDef.angle = obj.getAngle() / 57.2958f;
  bodyDef.angularDamping = obj.getAngularDamping();
  bodyDef.angularVelocity = obj.getAngularVelocity();
  bodyDef.awake = obj.isAwake();
  bodyDef.bullet = obj.isBullet();
  bodyDef.fixedRotation = obj.isFixedRotation();
  bodyDef.gravityScale = obj.getGravityScale();
  bodyDef.linearDamping = obj.getLinearDamping();
  ::std::cout << "LIN VEL: " << obj.getLinearVelocity().first << ", " << obj.getLinearVelocity().second << ::std::endl;
  bodyDef.linearVelocity.Set(obj.getLinearVelocity().first, obj.getLinearVelocity().second);
  bodyDef.position.Set(obj.getPosition().first / 32.0f, obj.getPosition().second / 32.0f);
  ::std::cout << "obj pos is: " << obj.getPosition().first << ", " << obj.getPosition().second << ::std::endl;
  ::std::cout << "body pos is: " << bodyDef.position.x << ", " << bodyDef.position.y << ::std::endl << ::std::endl;
  b2Body *newBody = mWorld.CreateBody(&bodyDef);

  // For all shapes we create the fixtures.
  for (const std::shared_ptr<internal::Shape> &shape: obj.getShapeGroup())
  {
    b2FixtureDef fixtureDef;
    fixtureDef.density = obj.getDensity();
    ::std::cout << "Density = " << fixtureDef.density << ::std::endl;
    fixtureDef.friction = obj.getFriction();
    fixtureDef.isSensor = obj.isSensor();
    fixtureDef.restitution = obj.getRestitution();

    b2Shape *newShape = nullptr;
    ::std::cout << "SHAPE TYPE IS: " << static_cast<int>(shape->getType()) << ::std::endl;
    if (shape->isValid() && shape->getType() == internal::Shape::Type::Box)
    {
      ::std::cout << "BOX SHAPE ATTACHED" << ::std::endl;
      const internal::Box *box = dynamic_cast<const internal::Box*>(shape.get());
      b2PolygonShape *polygonShape = new b2PolygonShape;
      polygonShape->SetAsBox(box->getWidth() / 2.0f / 32.0f, box->getHeight() / 2.0f / 32.0f);
      newShape = polygonShape;
    }
    else if (shape->isValid() && shape->getType() == internal::Shape::Type::Circle)
    {
      ::std::cout << "CIRCLE SHAPE ATTACHED" << ::std::endl;
      const internal::Circle *circle = dynamic_cast<const internal::Circle*>(shape.get());
      b2CircleShape *circleShape = new b2CircleShape;
      circleShape->m_radius = circle->getRadius() / 32.0f;
      ::std::cout <<" Circle radius = " << circleShape->m_radius << ::std::endl;
      newShape = circleShape;
      ball = newBody;
      ::std::cout << ">>>>Object pos is " << ball->GetPosition().x << ", " << ball->GetPosition().y << ::std::endl;
    }

    if (newShape != nullptr)
    {
      fixtureDef.shape = newShape;
      b2Fixture *newFixture = newBody->CreateFixture(&fixtureDef); // TODO: Destroy on removal.
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
  physObj.setAngle(body.GetAngle() * 57.2958f);
  physObj.setAngularDamping(body.GetAngularDamping());
  physObj.setAngularVelocity(body.GetAngularVelocity());
  physObj.setAwake(body.IsAwake());
  physObj.setBullet(body.IsBullet());
  physObj.setFixedRotation(body.IsFixedRotation());
  physObj.setGravityScale(body.GetGravityScale());
  physObj.setLinearDamping(body.GetLinearDamping());
  // TODO: linear velocity.
  physObj.setLinearVelocity(LinearVelocity(body.GetLinearVelocity().x, body.GetLinearVelocity().y));
  physObj.setPosition(std::make_pair(body.GetPosition().x * 32.0f, body.GetPosition().y * 32.0f));
  body.GetFixtureList();
  physObj.setChanged();
}

} // namespace ibrengine
