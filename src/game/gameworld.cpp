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
      for (const std::shared_ptr<ibrengine::MapObject> &mapObj: *layer)
      {
        if (mapObj.get()->getType() == "main_character")
          this->initMainCharacter(mapObj.get());
        objects++;
      }
    }
    std::cout << "OBJECTS: " << objects << std::endl;
  }
}

void GameWorld::draw(sf::RenderTarget &target)
{
}

void GameWorld::handleInput(Input::Action act)
{
  sf::Vector2i pos(mMainCharacter->getPosition());
  pos.x += 10.0f;
  mMainCharacter->setPosition(pos);
}

void GameWorld::update()
{
}

MainCharacter* GameWorld::getMainCharacter()
{
  return mMainCharacter.get();
}

void GameWorld::initMainCharacter(const ibrengine::MapObject *mapObj)
{
  mMainCharacter.reset(new MainCharacter);
  mMainCharacter->setPosition(mapObj->getPosition());
  if (mapObj->hasProperty("anim_walk_r"))
  {
    // Set animation.
    int animId = ibrengine::utils::stdStringToInt(mapObj->getProperty("anim_walk_r"));
    mMainCharacter->setAnimation(MainCharacter::Animation::WalkRight,
      mMap->getAnimation(animId));
    mMainCharacter->setCurrentAnimation(MainCharacter::Animation::WalkRight);
    // Set health.
    int health = ibrengine::utils::stdStringToInt(mapObj->getProperty("health"));
    mMainCharacter->setHealth(health);
  }
}
