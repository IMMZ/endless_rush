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
  int fr1 = mMap->getAnimation(1)->getFramesCount();
  int fr2 = mMap->getAnimation(2)->getFramesCount();
  std::cout << "fr1 = " << fr1 << "; fr2 " << fr2 << std::endl;
  const sf::View *defaultView = &this->getRenderTarget()->getView(); // TODO: extra
  if (act == Input::Action::Pause)
    this->requestStateChange(GameState::Pause);
  else if (act == Input::Action::Right)
  {
    sf::View view(defaultView->getCenter(), defaultView->getSize());
    view.move(10.0f, 0.0f);
    this->getRenderTarget()->setView(view);
  }
  else if (act == Input::Action::Left)
  {
    sf::View view(defaultView->getCenter(), defaultView->getSize());
    view.move(-10.0f, 0.0f);
    this->getRenderTarget()->setView(view);
  }
  else if (act == Input::Action::Down)
  {
    sf::View view(defaultView->getCenter(), defaultView->getSize());
    view.move(0.0f, 10.0f);
    this->getRenderTarget()->setView(view);
  }
  else if (act == Input::Action::Up)
  {
    sf::View view(defaultView->getCenter(), defaultView->getSize());
    view.move(0.0f, -10.0f);
    this->getRenderTarget()->setView(view);
  }
}

void InGameState::update()
{
  // TODO: implement
}

void InGameState::setMap(const ibrengine::Map *map)
{
  mMap = map;
}

} // namespace internal
