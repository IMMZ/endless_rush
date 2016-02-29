// todo: license

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

namespace ibrengine
{

namespace utils
{

std::string extractFilenameFromPath(const std::string &filePath);
void splitString(const std::string &str, char splitChar, bool includeEmpty, std::vector<std::string> &result);
std::string IntToStdString(int i);
std::string floatToStdString(float f);
sf::Color hexColorToSFMLColor(const std::string &hexColor);
bool stringToBool(const sf::String &str);

template <typename T>
T stdStringToNumber(const std::string &str)
{
  std::stringstream ss; T value;
  ss << str; ss >> value;
  return value;
}

template <typename T>
std::string NumberToStdString(T num)
{
  std::stringstream ss; std::string value;
  ss << num; ss >> value;
  return value;
}

template <typename T>
void sfStringToVector2d(const sf::String &str, std::pair<T, T> &vector)
{
  std::string s(str);
  std::string::size_type pos = s.find(';');
  if (pos != std::string::npos)
  {
    const std::string firstNum(s.substr(0, pos));
    const std::string secondNum(s.substr(pos + 1, s.length() - pos));
    vector.first = stdStringToNumber<T>(firstNum);
    vector.second = stdStringToNumber<T>(secondNum);
  }
}

} // namespace utils

} // namespace ibrengine

#endif // UTILS_HPP
