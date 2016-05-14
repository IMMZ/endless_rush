// TODO: license

#include "ingamestate.hpp"

#include "game.hpp"

#include <map.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include <cassert>
#include <iostream> // TODO; remove

#include <debugdraw.hpp>

namespace internal
{

InGameState::InGameState():
  mRenderer(nullptr),
  mPhysicWorld(new ibrengine::PhysicWorld(*(dynamic_cast<ibrengine::DebugDraw*>(getRenderTarget()))))
{
  this->setUsedSound("rush.ogg");
}

void InGameState::draw(sf::RenderTarget &target)
{
  assert(mMap != nullptr);
  if (mRenderer.get() == nullptr)
    mRenderer.reset(new ibrengine::MapRenderer(target));
  mRenderer->renderMap(mMap);
  mPhysicWorld->draw();
}

void InGameState::handleInput(Input::Action act)
{
  if (act == Input::Action::Down)
    Game::instance().setSpeed(0.5f);
  else if (act == Input::Action::Up)
    Game::instance().setSpeed(1.0f);
  mGameWorld->handleInput(act);
}

void InGameState::update(const sf::Time &time)
{
  mGameWorld->update();
  mMap->update(time);
  mPhysicWorld->update(time);
}

void InGameState::setMap(ibrengine::Map *map)
{
  mMap = map;
  mGameWorld.reset(new GameWorld(mMap));
  mPhysicWorld->initFromMap(*mMap);
}

} // namespace internal
