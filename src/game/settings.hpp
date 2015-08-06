// TODO: license

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "input.hpp"

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
  Settings() {};
  Settings(const Settings &other);
  Settings(const Settings &&other);
  Settings& operator=(const Settings &other);

  std::map<sf::Keyboard::Key, Input::Action> mActions;
  sf::VideoMode mVideoMode;
};

#endif // SETTINGS_HPP
