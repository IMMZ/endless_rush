// TODO: license text

#ifndef PHYSICWORLD_HPP
#define PHYSICWORLD_HPP

#include <Box2D/Dynamics/b2World.h>

#include <memory>
#include <vector>

namespace sf
{
  class Time;
}

namespace ibrengine
{

class Map;
class PhysicObject;

class PhysicWorld
{
public:
  PhysicWorld();
  ~PhysicWorld();

  void update(const sf::Time &time);

  void initFromMap(const Map &map);

private:
  static const int32 VelocityIterations = 10;
  static const int32 PositionIterations = 10;

  void createBody(const PhysicObject &obj);
  void changePhysicObject(const b2Body &body, PhysicObject &physObj);

  b2World mWorld;
  std::vector<b2Body*> mBodies;
  std::unique_ptr<b2ContactListener> mContactListener;
  b2Body *ball = nullptr;
};

} // namespace ibrengine

#endif // PHYSICWORLD_HPP
