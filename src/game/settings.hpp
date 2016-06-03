// TODO: license

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "input.hpp"

#include <global.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <map>

class Settings
{
public:
  static Settings& instance();
  void init();
  Input::Action getAction(sf::Keyboard::Key key);
  const sf::VideoMode& getVideoMode() const;
  void setVideoMode(const sf::VideoMode &size);

private:
  DISABLE_COPY(Settings);
  DISABLE_MOVE(Settings);
 
  Settings() = default;

  std::map<sf::Keyboard::Key, Input::Action> mActions;
  sf::VideoMode mVideoMode;
};

#endif // SETTINGS_HPP
