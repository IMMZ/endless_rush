// TODO: license

#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "igamestate.hpp"

#include <vector>

namespace internal
{

class IntroState: public IGameState
{
public:
  IntroState();

  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update() override;

private:
  enum class TextState
  {
    FadeIn,
    Normal,
    FadeOut
  };

  bool hasNextText();
  void setNextText();

  static const int ALPHA_CHANGING_INTERVAL_MS = 100;
  static const int ALPHA_CHANGE_VALUE = 30;

  const std::vector<sf::String> mTexts =
  {
    "IbramLab presents",
    "Programming by Mamed Ibrahimov",
    "Music by Goryn Doroshenko",
    "Russia, 2015"
  };
  sf::Font mFont;
  sf::Text mText;
  sf::Clock mTimer;
  sf::Color mTextColor = sf::Color(255, 255, 255, 0);
  TextState mTextState = TextState::FadeIn;
  int mCurrentText = 0;
};

} // namespace internal

#endif // INTROSTATE_HPP
