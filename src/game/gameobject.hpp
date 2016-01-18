// license text

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/System/Vector2.hpp>

namespace ibrengine
{

class Object;

}

namespace sf
{

class RenderTarget;

}

class GameObject
{
public:
  explicit GameObject(ibrengine::Object *mapObj);

  const sf::Vector2i& getPosition() const;
  void setPosition(const sf::Vector2i &pos);

protected:
  ibrengine::Object* getMapObj();

private:
  ibrengine::Object *mMapObj = nullptr;
};

#endif // GAMEOBJECT_HPP
