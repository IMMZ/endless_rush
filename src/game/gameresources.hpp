// license text

#ifndef GAMERESOURCES_HPP
#define GAMERESOURCES_HPP

#include <animation.hpp>

#include <map>
#include <memory>

class GameResources
{
public:
  static GameResources& instance();
  void load();


private:
  GameResources() {}
  GameResources(const GameResources &gr);
  GameResources(const GameResources &&gr);
  GameResources& operator=(const GameResources &gr);
};

#endif // GAMERESOURCES_HPP
