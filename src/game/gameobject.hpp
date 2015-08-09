// license text

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/System/Vector2.hpp>

namespace ibrengine
{

class MapObject;

}

namespace sf
{

class RenderTarget;

}

class GameObject
{
public:
  explicit GameObject(ibrengine::MapObject *mapObj);

  const sf::Vector2i& getPosition() const;
  void setPosition(const sf::Vector2i &pos);

protected:
  ibrengine::MapObject* getMapObj();

private:
  ibrengine::MapObject *mMapObj = nullptr;
};

#endif // GAMEOBJECT_HPP
