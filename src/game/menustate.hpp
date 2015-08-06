// TODO: license

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "igamestate.hpp"

namespace internal
{

class MenuState: public IGameState
{
public:
  // IGameState
  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update() override;
};

} // namespace internal

#endif
