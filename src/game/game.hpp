// TODO: license text

#ifndef GAME_HPP
#define GAME_HPP

#include "igamestate.hpp"

#include <SFML/System/Time.hpp>

#include <memory>
#include <string>

namespace ibrengine
{

class Map;

}

class Game
{
public:
  static Game& instance();

  void init();
  void free();
  void start();

  GameState getState() const;
  void setState(GameState state);

private:
  static const std::string NAME;
  static const sf::Time UPDATES_PER_SECOND;

  Game() {};
  Game(const Game &other);
  Game(const Game &&other);
  Game operator=(const Game &other);

  internal::IGameState *mCurrentState = nullptr;
  std::unique_ptr<internal::IGameState>
    mIntroState,
    mMenuState,
    mOptionsState,
    mBonusesState,
    mLevelLoadingState,
    mInGameState,
    mPauseState,
    mTitlesState;
  GameState mState = GameState::Menu;
  ibrengine::Map *mCurrentMap = nullptr;
};

#endif // GAME_HPP
