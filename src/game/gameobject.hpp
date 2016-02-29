// license text

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <global.hpp>

namespace ibrengine
{

class Object;

}

class GameObject
{
public:
  explicit GameObject(ibrengine::Object *mapObj);

  const ibrengine::PositionI& getPosition() const;
  void setPosition(const ibrengine::PositionI &pos);

protected:
  ibrengine::Object* getMapObj();

private:
  ibrengine::Object *mMapObj = nullptr;
};

#endif // GAMEOBJECT_HPP
