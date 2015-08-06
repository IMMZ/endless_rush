// license text

#include "gameresources.hpp"

#include <SFML/System/String.hpp>

#include <vector>

GameResources& GameResources::instance()
{
  static GameResources gameRes;
  return gameRes;
}

void GameResources::load()
{
}
