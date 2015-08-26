// TODO: license

#include "introstate.hpp"

#include "game.hpp"
#include "global.hpp"
#include "utils.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream> // TODO: remove

/*
 * TODO: implement
 * 1) Set texts' position.
 * 2) Start the timer.
 * 3) Handle text chaning
 */

namespace internal
{

IntroState::IntroState()
{
  mFont.loadFromFile("font.ttf"); // TODO: handle loading error
  mText.setString(mTexts[mCurrentText]);
  mText.setFont(mFont);
  mText.setCharacterSize(40);
  utils::centerText(mText);
}

void IntroState::draw(sf::RenderTarget &target)
{
  target.draw(mText);
}

void IntroState::handleInput(Input::Action act)
{
  // Intro isn't skipped.
  unused(act);
}

void IntroState::update(const sf::Time &time)
{
  switch (mTextState)
  {
    case TextState::FadeIn:
    {
      // Decreasing alpha by timer while it will be 0 then go to the Normal state.
      if (mTimer.getElapsedTime().asMilliseconds() >= ALPHA_CHANGING_INTERVAL_MS)
      {
        if ((mTextColor.a + ALPHA_CHANGE_VALUE) < 256)
        {
          mTextColor.a += ALPHA_CHANGE_VALUE;
        }
        else
        {
          mTextColor.a = 255;
          mTextState = TextState::Normal;
        }
        mText.setColor(mTextColor);
        mTimer.restart();
      }
      break;
    }
    case TextState::Normal:
    {
      // Wait 3 sec and go to the FadeOut state.
      if (mTimer.getElapsedTime().asSeconds() >= 3 )
      {
        mTextState = TextState::FadeOut;
        mTimer.restart();
      }
      break;
    }
    case TextState::FadeOut:
    {
      if (mTimer.getElapsedTime().asMilliseconds() >= ALPHA_CHANGING_INTERVAL_MS)
      {
        // Decreasing alpha by timer while it will be a 255, then go to the next text.
        if (mTextColor.a >= ALPHA_CHANGE_VALUE)
        {
          mTextColor.a -= ALPHA_CHANGE_VALUE;
        }
        else
        {
          if (this->hasNextText())
          {
            this->setNextText();
            mTextState = TextState::FadeIn;
          }
          else
          {
            this->requestStateChange(GameState::Menu);
            break;
          }
        }
        mText.setColor(mTextColor);
        mTimer.restart();
      }
      break;
    }
    default: break;
  }
}

bool IntroState::hasNextText()
{
  return mCurrentText < (mTexts.size() - 1);
}

void IntroState::setNextText()
{
  if (this->hasNextText())
    mCurrentText++;
  mText.setString(mTexts[mCurrentText]);
  utils::centerText(mText);
}

} // namespace internal
