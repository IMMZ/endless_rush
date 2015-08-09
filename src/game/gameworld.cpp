// license text

#include "gameworld.hpp"

#include <map.hpp>
#include <objectlayer.hpp>
#include <utils.cpp>

#include <iostream> // TOOD: remove

GameWorld::GameWorld(ibrengine::Map *map):
  mMap(map)
{
  for (ibrengine::Map::LayerConstIterator i = mMap->layersBegin(); i != mMap->layersEnd(); ++i)
  {
    ibrengine::ObjectLayer *layer = dynamic_cast<ibrengine::ObjectLayer*>(i->get());
    int objects = 0;
    if (layer != nullptr)
    {
      for (std::shared_ptr<ibrengine::MapObject> &mapObj: *layer)
      {
        if (mapObj->hasProperty("game_obj_type")
            && mapObj->getProperty("game_obj_type") == "main_character")
          this->initMainCharacter(mapObj.get());
        objects++;
      }
    }
  }
}

void GameWorld::draw(sf::RenderTarget &target)
{
}

void GameWorld::handleInput(Input::Action act)
{
  sf::Vector2i pos(mMainCharacter->getPosition());
  switch (act)
  {
    case Input::Action::Right:
    {
      pos.x += 2.0f;
      break;
    }
    case Input::Action::Left:
    {
      pos.x -= 2.0f;
      break;
    }
    case Input::Action::Up:
    {
      pos.y -= 2.0f;
      break;
    }
    case Input::Action::Down:
    {
      pos.y += 2.0f;
      break;
    }
    case Input::Action::Fire:
    {
      if (mMainCharacter->getState() == MainCharacter::State::Staying)
        mMainCharacter->setState(MainCharacter::State::Beating);
      else
        mMainCharacter->setState(MainCharacter::State::Staying);
      break;
    }
  }

  mMainCharacter->setPosition(pos);
}

void GameWorld::update()
{
  mMainCharacter->update();
}

MainCharacter* GameWorld::getMainCharacter()
{
  return mMainCharacter.get();
}

void GameWorld::initMainCharacter(ibrengine::MapObject *mapObj)
{
  mMainCharacter.reset(new MainCharacter(mapObj));
  mMainCharacter->setPosition(mapObj->getPosition());
  // Set health.
  int health = ibrengine::utils::stdStringToInt(mapObj->getProperty("health"));
  mMainCharacter->setHealth(health);
}
