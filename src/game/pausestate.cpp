// TODO: license

#include "pausestate.hpp"

#include "game.hpp"
#include "settings.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream> // TODO: remove
namespace internal
{

PauseState::PauseState()
{
  mRect.setFillColor(sf::Color(0, 0, 128, 100)); // Transparent blue color.
  mRect.setSize(sf::Vector2f(
    static_cast<float>(Settings::instance().getVideoMode().width),
    static_cast<float>(Settings::instance().getVideoMode().height)));
}

void PauseState::draw(sf::RenderTarget &target)
{
  target.draw(mRect);
}

void PauseState::handleInput(Input::Action act)
{
  if (act == Input::Action::Pause)
    this->requestStateChange(GameState::InGame);
}

void PauseState::update(const sf::Time &time)
{
  // TODO: implement
}

} // namespace internal
