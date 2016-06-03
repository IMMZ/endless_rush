// TODO: license text

#ifndef GAME_HPP
#define GAME_HPP

#include "igamestate.hpp"

#include <global.hpp>
#include <map.hpp>

#include <SFML/System/Time.hpp>

#include <memory>
#include <string>

class Game
{
public:
  static Game& instance();

  void init();
  void free();
  void start();

  GameState getState() const;
  void setState(GameState state);
  float getSpeed() const;
  void setSpeed(float speed);

private:
  DISABLE_COPY(Game);
  DISABLE_MOVE(Game);

  static const std::string NAME;
  static const sf::Time UPDATES_PER_SECOND;

  Game() = default;

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
  GameState mState = GameState::InGame;
  std::unique_ptr<ibrengine::Map> mCurrentMap = { nullptr };
  float mSpeed = 1.0f;
};

#endif // GAME_HPP
