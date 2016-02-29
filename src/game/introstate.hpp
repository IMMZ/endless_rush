// TODO: license

#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "igamestate.hpp"

#include <array>

namespace internal
{

class IntroState: public IGameState
{
public:
  IntroState();

  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update(const sf::Time &time) override;

private:
  enum class TextState
  {
    FadeIn,
    Normal,
    FadeOut
  };

  bool hasNextText();
  void setNextText();

  static constexpr int ALPHA_CHANGING_INTERVAL_MS = 100;
  static constexpr int ALPHA_CHANGE_VALUE = 30;

  static const std::array<sf::String, 4> mTexts;

  sf::Font mFont;
  sf::Text mText;
  sf::Clock mTimer;
  sf::Color mTextColor = sf::Color(255, 255, 255, 0);
  TextState mTextState = TextState::FadeIn;
  int mCurrentText = 0;
};

} // namespace internal

#endif // INTROSTATE_HPP
