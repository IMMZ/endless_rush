// license text

#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "input.hpp"
#include "maincharacter.hpp"

#include <memory>

class MainCharacter;

namespace ibrengine
{

class Map;
class MapObject;

}

namespace sf
{

class RenderTarget;

}

class GameWorld
{
public:
  GameWorld(ibrengine::Map *map);

  void draw(sf::RenderTarget &target);
  void handleInput(Input::Action act);
  void update();

  MainCharacter *getMainCharacter();

private:
  void initMainCharacter(ibrengine::MapObject *mapObj);

  ibrengine::Map *mMap;
  std::unique_ptr<MainCharacter> mMainCharacter;
};

#endif // GAMEWORLD_HPP
