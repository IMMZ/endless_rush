// TODO: license

#include "levelloadingstate.hpp"

#include "global.hpp"
#include "utils.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace internal
{

LevelLoadingState::LevelLoadingState(const sf::String &path)
{
  mUsedFont.loadFromFile("font.ttf");
  if (mTexture.loadFromFile(path))
  {
    mSprite.setTexture(mTexture, true);
    mTextureLoaded = true;
  }
  mLoadingText.setString("Loading...");
  mLoadingText.setPosition(300.0f, 570.0f);
  mLoadingText.setFont(mUsedFont);
  mPressEnterText.setString("Press Enter to start the level");
  mPressEnterText.setPosition(300.0f, 570.0f);
  mPressEnterText.setFont(mUsedFont);
  utils::centerText(mLoadingText);
}

void LevelLoadingState::draw(sf::RenderTarget &target)
{
  if (mTextureLoaded)
    target.draw(mSprite);
  if (!mLevelLoaded)
  {
    target.draw(mLoadingText);
  }
  else if (mPressEnterTextVisible)
    target.draw(mPressEnterText);
}

void LevelLoadingState::handleInput(Input::Action act)
{
  if (mLevelLoaded && act == Input::Action::Start)
    this->requestStateChange(GameState::InGame);
}

void LevelLoadingState::update()
{
  if (mLevelLoaded)
  {
    if (mTimer.getElapsedTime().asMilliseconds() >= PRESS_ENTER_TEXT_BLINK_INTERVAL_MS)
    {
      mPressEnterTextVisible = !mPressEnterTextVisible;
      mTimer.restart();
    }
  }
}

void LevelLoadingState::setMapFile(const sf::String &mapFilePath)
{
  mMapFile = mapFilePath;
}

void LevelLoadingState::loadMap()
{
  mLoadedMap = mTmxLoader.loadMap(mMapFile.toAnsiString());
  mLevelLoaded = true;
}

ibrengine::Map* LevelLoadingState::loadedMap() // TODO: use smart ptr.
{
  return mLoadedMap;
}

} // namespace internal
