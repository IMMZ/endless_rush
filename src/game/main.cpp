#include "game.hpp"

int main()
{
  Game::instance().init();
  Game::instance().start();
  Game::instance().free();
  return 0;
}