// TODO: license text

#include "titlesstate.hpp"

#include <SFML/Graphics/Text.hpp>

namespace internal
{

void TitlesState::draw(sf::RenderTarget &target)
{
  for (Participant p: mParticipants)
  {
    sf::Text role;
    role.setString(p.first);

  }
}

void TitlesState::handleInput(Input::Action act)
{
}

void TitlesState::update(const sf::Time &time)
{
}

} // namespace internal
