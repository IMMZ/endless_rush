// license text

#ifndef GAMERESOURCES_HPP
#define GAMERESOURCES_HPP

#include <animation.hpp>
#include <global.hpp>

#include <map>
#include <memory>

class GameResources
{
public:
  static GameResources& instance();
  void load();

private:
  DISABLE_COPY(GameResources);
  DISABLE_MOVE(GameResources);

  GameResources() = default;
};

#endif // GAMERESOURCES_HPP
