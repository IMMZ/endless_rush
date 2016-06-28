// TODO: license text

#ifndef PHYSICOBJECT_HPP_
#define PHYSICOBJECT_HPP_

#include "object.hpp"
#include "shape.hpp"

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Common/b2Settings.h>

#include <memory>
#include <vector>

namespace ibrengine
{

class PhysicObject: public Object
{
public:
  using ShapeGroup = std::vector<std::shared_ptr<internal::Shape>>;

  enum class Type
  {
    Static = b2_staticBody,
    Kinematic = b2_kinematicBody,
    Dynamic = b2_dynamicBody
  };

  explicit PhysicObject(const MapUnitPtr &director, int id, Type t = Type::Static);

  bool isActive() const;
  void setActive(bool active);
  bool isAllowSleep() const;
  void setAllowSleep(bool allowSleep);
  float32 getAngle() const;
  void setAngle(float32 angle);
  float32 getAngularDamping() const;
  void setAngularDamping(float32 angularDamping);
  float32 getAngularVelocity() const;
  void setAngularVelocity(float32 angularVelocity);
  bool isAwake() const;
  void setAwake(bool awake);
  bool isBullet() const;
  void setBullet(bool bullet);
  bool isFixedRotation() const;
  void setFixedRotation(bool fixedRotation);
  float32 getGravityScale() const;
  void setGravityScale(float32 gravityScale);
  float32 getLinearDamping() const;
  void setLinearDamping(float32 linearDamping);
  const LinearVelocity& getLinearVelocity() const;
  void setLinearVelocity(const LinearVelocity &linearVelocity);
  Type getType() const;
  void setType(Type type);
  float32 getDensity() const;
  void setDensity(float32 density);
  float32 getFriction() const;
  void setFriction(float32 friction);
  bool isSensor() const;
  void setSensor(bool sensor);
  float32 getRestitution() const;
  void setRestitution(float32 restitution);
  const ShapeGroup& getShapeGroup() const;
  void setShapeGroup(const ShapeGroup &shape);

  // Object
  void update(const sf::Time &time) override;

private:
  ShapeGroup mShapeGroup;
  LinearVelocity mLinearVelocity;
  float32 mAngle = 0.0f, mAngularDamping = 0.0f, mAngularVelocity = 0.0f,
    mDensity = 0.0f, mFriction = 0.0f, mGravityScale = 1.0f,
    mLinearDamping = 0.0f, mRestitution = 0.0f;
  bool mActive = true, mAllowSleep = true, mAwake = true, mBullet = false,
    mFixedRotation = false, mSensor = false;
  Type mType = Type::Static;
};

using PhysicalObjectScopedPtr = std::unique_ptr<PhysicObject>;
using PhysicalObjectSharedPtr = std::shared_ptr<PhysicObject>;
using PhysicalObjectWeakPtr = std::weak_ptr<PhysicObject>;

} // namespace ibrengine

#endif // PHYSICOBJECT_HPP_
