// TODO: license text

#include "mapobject.hpp"
#include "physicobject.hpp"

namespace ibrengine
{

PhysicObject::PhysicObject(const MapUnitPtr &director, Type type):
  Object(director, Object::Type::Physical),
  mType(type)
{
  //if (mType == Type::Dynamic)
  mDensity = 1.0f;
  director->setObject(this);
}

bool PhysicObject::isActive() const
{
  return mActive;
}

void PhysicObject::setActive(bool active)
{
  mActive = active;
}

bool PhysicObject::isAllowSleep() const
{
  return mAllowSleep;
}

void PhysicObject::setAllowSleep(bool allowSleep)
{
  mAllowSleep = allowSleep;
}

float32 PhysicObject::getAngle() const
{
  return mAngle;
}

void PhysicObject::setAngle(float32 angle)
{
  mAngle = angle;
}

float32 PhysicObject::getAngularDamping() const
{
  return mAngularDamping;
}

void PhysicObject::setAngularDamping(float32 angularDamping)
{
  mAngularDamping = angularDamping;
}

float32 PhysicObject::getAngularVelocity() const
{
  return mAngularVelocity;
}

void PhysicObject::setAngularVelocity(float32 angularVelocity)
{
  mAngularVelocity = angularVelocity;
}

bool PhysicObject::isAwake() const
{
  return mAwake;
}

void PhysicObject::setAwake(bool awake)
{
  mAwake = awake;
}

bool PhysicObject::isBullet() const
{
  return mBullet;
}

void PhysicObject::setBullet(bool bullet)
{
  mBullet = bullet;
}

bool PhysicObject::isFixedRotation() const
{
  return mFixedRotation;
}

void PhysicObject::setFixedRotation(bool fixedRotation)
{
  mFixedRotation = fixedRotation;
}

float32 PhysicObject::getGravityScale() const
{
  return mGravityScale;
}

void PhysicObject::setGravityScale(float32 gravityScale)
{
  mGravityScale = gravityScale;
}

float32 PhysicObject::getLinearDamping() const
{
  return mLinearDamping;
}

void PhysicObject::setLinearDamping(float32 linearDamping)
{
  mLinearDamping = linearDamping;
}

const LinearVelocity& PhysicObject::getLinearVelocity() const
{
  return mLinearVelocity;
}

void PhysicObject::setLinearVelocity(const LinearVelocity &linearVelocity)
{
  mLinearVelocity = linearVelocity;
}

PhysicObject::Type PhysicObject::getType() const
{
  return mType;
}

void PhysicObject::setType(Type type)
{
  mType = type;
}

float32 PhysicObject::getDensity() const
{
  return mDensity;
}

void PhysicObject::setDensity(float32 density)
{
  mDensity = density;
}

float32 PhysicObject::getFriction() const
{
  return mFriction;
}

void PhysicObject::setFriction(float32 friction)
{
  mFriction = friction;
}

bool PhysicObject::isSensor() const
{
  return mSensor;
}

void PhysicObject::setSensor(bool sensor)
{
  mSensor = sensor;
}

float32 PhysicObject::getRestitution() const
{
  return mRestitution;
}

void PhysicObject::setRestitution(float32 restitution)
{
  mRestitution = restitution;
}

const PhysicObject::ShapeGroup& PhysicObject::getShapeGroup() const
{
  return mShapeGroup;
}

void PhysicObject::setShapeGroup(const ShapeGroup &shape)
{
  mShapeGroup = shape;
}

void PhysicObject::update(const sf::Time &time)
{
}

} // namespace ibrengine
