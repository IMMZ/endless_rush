// TODO: license

#include "ingamestate.hpp"

#include "game.hpp"

#include <map.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include <cassert>
#include <iostream> // TODO; remove
namespace internal
{

InGameState::InGameState():
  mRenderer(nullptr)
{
}

void InGameState::draw(sf::RenderTarget &target)
{
  assert(mMap != nullptr);
  if (mRenderer.get() == nullptr)
    mRenderer.reset(new ibrengine::MapRenderer(target));
  mRenderer->renderMap(mMap);
}

void InGameState::handleInput(Input::Action act)
{
  mGameWorld->handleInput(act);
}

void InGameState::update(const sf::Time &time)
{
  mGameWorld->update();
  mMap->update(time);
}

void InGameState::setMap(ibrengine::Map *map)
{
  mMap = map;
  mGameWorld.reset(new GameWorld(mMap));
}

} // namespace internal
