// TODO: license

#include "gamestate.hpp"
#include "menustate.hpp"
#include "utils.hpp"

#include <SFML/Graphics/Font.hpp> // TODO: remove
#include <SFML/Graphics/Text.hpp> // TODO: remove
#include <SFML/Graphics/RenderTarget.hpp>

namespace internal
{

void MenuState::draw(sf::RenderTarget &target)
{
  sf::Text txt;
  sf::Font font;
  font.loadFromFile("font.ttf");
  txt.setFont(font);
  txt.setString("This is instead of MENU");
  txt.setCharacterSize(100);
  utils::centerText(txt);
  target.draw(txt);
}

void MenuState::handleInput(Input::Action act)
{
  if (act == Input::Action::Start)
    this->requestStateChange(GameState::LoadingLevel);
}

void MenuState::update(const sf::Time &time)
{
  // TODO: implement
}

} // namespace internal
