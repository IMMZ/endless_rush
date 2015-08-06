#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "igamestate.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace internal
{

class PauseState: public IGameState
{
public:
  PauseState();

  // IGameState
  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update() override;

private:
  sf::RectangleShape mRect;
};

} // namespace internal

#endif // PAUSESTATE_HPP
