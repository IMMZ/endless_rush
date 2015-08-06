// license text

#include "settings.hpp"

Settings& Settings::instance()
{
  static Settings s;
  return s;
}

void Settings::init()
{
  mVideoMode.width = 800;
  mVideoMode.height = 640;
  // mVideoMode.bitsPerPixel = 24; TODO: set up the bpp
}

Input::Action Settings::getAction(sf::Keyboard::Key key)
{ // Avoid hard-coding. TODO: read from settings.
  switch (key)
  {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
      return Input::Action::Up;
    case sf::Keyboard::A:
    case sf::Keyboard::Left:
      return Input::Action::Left;
    case sf::Keyboard::S:
    case sf::Keyboard::Down:
      return Input::Action::Down;
    case sf::Keyboard::D:
    case sf::Keyboard::Right:
      return Input::Action::Right;
    case sf::Keyboard::Return:
      return Input::Action::Start;
    case sf::Keyboard::SemiColon:
      return Input::Action::Fire;
    case sf::Keyboard::Quote:
      return Input::Action::Jump;
    case sf::Keyboard::L:
      return Input::Action::SuperMove;
    case sf::Keyboard::Escape:
    case sf::Keyboard::BackSlash:
      return Input::Action::Back;
  }
  return Input::Action::NoAction;
}

const sf::VideoMode& Settings::getVideoMode() const
{
  return mVideoMode;
}

void Settings::setVideoMode(const sf::VideoMode &videoMode)
{
  mVideoMode = videoMode;
}
