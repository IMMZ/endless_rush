// TODO: license

#ifndef LEVELLOADINGSTATE_HPP
#define LEVELLOADINGSTATE_HPP

#include "igamestate.hpp"

#include "tmxloader.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace internal
{

class LevelLoadingState: public IGameState
{
public:
  LevelLoadingState(const sf::String &imgPath);

  // IGameState
  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update(const sf::Time &time) override;

  void setMapFile(const sf::String &mapFilePath);
  std::unique_ptr<ibrengine::Map> loadMap();

private:
  static const int PRESS_ENTER_TEXT_BLINK_INTERVAL_MS = 500;

  ibrengine::TmxLoader mTmxLoader;
  sf::Texture mTexture;
  sf::Sprite mSprite;
  sf::Text mLoadingText, mPressEnterText;
  sf::Font mUsedFont;
  sf::String mMapFile;
  sf::Clock mTimer;
  bool mTextureLoaded = false;
  bool mLevelLoaded = false;
  bool mPressEnterTextVisible = true;
};

} // namespace internal

#endif // LEVELLOADINGSTATE_HPP
