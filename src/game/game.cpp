// TODO: license text

#include "game.hpp"

#include "gameresources.hpp"
#include "input.hpp"
#include "ingamestate.hpp"
#include "introstate.hpp"
#include "levelloadingstate.hpp"
#include "menustate.hpp"
#include "pausestate.hpp"
#include "settings.hpp"

#include <map.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

const std::string Game::NAME = "Endless shit";
const sf::Time Game::UPDATES_PER_SECOND = sf::seconds(1.0f / 60.0f);

Game& Game::instance()
{
  static Game game;
  return game;
}

void Game::init()
{
  Settings::instance().init();
  GameResources::instance().load();
  mIntroState.reset(new internal::IntroState);
  mMenuState.reset(new internal::MenuState);
  mInGameState.reset(new internal::InGameState);
  mLevelLoadingState.reset(new internal::LevelLoadingState("loading.jpg"));
  mPauseState.reset(new internal::PauseState);
  mCurrentState = mMenuState.get();
  // TODO: init the rest
}

void Game::start()
{
  this->setState(mState);
  sf::RenderWindow window(Settings::instance().getVideoMode(), NAME);

  mIntroState.get()->setRenderTarget(&window);
  mMenuState.get()->setRenderTarget(&window);
  mInGameState.get()->setRenderTarget(&window);
  mLevelLoadingState.get()->setRenderTarget(&window);
  mPauseState.get()->setRenderTarget(&window);

  sf::Clock timer;
  sf::Time elapsedTime = sf::Time::Zero;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
        {
          window.close(); break;
        }
        case sf::Event::KeyPressed:
        {
          Input::Action act = Settings::instance().getAction(event.key.code);
          mCurrentState->handleInput(act);
          break;
        }
      }
    }
    elapsedTime += timer.restart();
    while (elapsedTime > UPDATES_PER_SECOND)
    {
      elapsedTime -= UPDATES_PER_SECOND;
      mCurrentState->update(UPDATES_PER_SECOND);
      if (mCurrentState->isStateChangeRequested())
        this->setState(mCurrentState->requestedState());
    }
    window.clear();
    mCurrentState->draw(window);
    window.display();
  }
}

void Game::free()
{
  mIntroState.reset(nullptr);
  mMenuState.reset(nullptr);
  mInGameState.reset(nullptr);
  mLevelLoadingState.reset(nullptr);
  mPauseState.reset(nullptr);
  // TODO: init the rest
}

GameState Game::getState() const
{
  return mState;
}

void Game::setState(GameState state)
{
  if (mState != state)
  {
    switch (state)
    {
      case GameState::Intro:
      {
        mCurrentState = mIntroState.get(); break;
      }
      case GameState::Menu:
      {
        mCurrentState = mMenuState.get(); break;
      }
      case GameState::Options: // TODO implement
      case GameState::Bonuses:
        break;
      case GameState::LoadingLevel:
      {
        internal::LevelLoadingState *levelLoadingState =
          dynamic_cast<internal::LevelLoadingState*>(mLevelLoadingState.get());
        levelLoadingState->setMapFile("test.tmx");
        mCurrentState = mLevelLoadingState.get();
        levelLoadingState->loadMap();
        mCurrentMap = levelLoadingState->loadedMap(); // rename 'getLoaded'
        break;
      }
      case GameState::InGame:
      {
        internal::InGameState *inGameState =
          dynamic_cast<internal::InGameState*>(mInGameState.get());
        inGameState->setMap(mCurrentMap);
        mCurrentState = mInGameState.get();
        break;
      }
      case GameState::Pause:
      {
        mCurrentState = mPauseState.get();
        break;
      }
      case GameState::Titles:
      default:
        break;
    }

    mState = state;
  }
}

