#ifndef UTILS_HPP
#define UTILS_HPP

#include "settings.hpp"

#include <SFML/Graphics/Text.hpp>

#include <iostream> // TODO: remove

namespace utils
{

inline void centerText(sf::Text &txt)
{
  int screenW = Settings::instance().getVideoMode().width;
  int screenH = Settings::instance().getVideoMode().height;
  txt.setPosition(
    screenW / 2 - txt.getGlobalBounds().width / 2,
    screenH / 2 - txt.getGlobalBounds().height / 2);
}

} // namespace utils

#endif // UTILS_HPP
