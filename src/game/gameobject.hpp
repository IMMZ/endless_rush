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

private:
  sf::Vector2i mPos;
  ibrengine::MapObject *mapObj = nullptr;
};

#endif // GAMEOBJECT_HPP
