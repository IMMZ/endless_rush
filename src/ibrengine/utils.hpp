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
std::vector<std::string> splitString(const std::string &str, char splitChar, bool includeEmpty);
sf::Color hexColorToSFMLColor(const std::string &hexColor);
bool stringToBool(const sf::String &str);

template <typename T>
T stdStringToNumber(const std::string &str)
{
  static_assert(std::is_integral<T>::value or std::is_floating_point<T>::value, "Integral type required");
  std::stringstream ss; T value;
  ss << str; ss >> value;
  return value;
}

template <typename T>
std::string NumberToStdString(T num)
{
  static_assert(std::is_integral<T>::value or std::is_floating_point<T>::value, "Integral type required");
  std::stringstream ss; std::string value;
  ss << num; ss >> value;
  return value;
}

template <typename T>
std::pair<T, T> sfStringToVector2d(const sf::String &str)
{
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Integral type required");
  std::pair<T, T> vector;
  std::string s(str);

  if (std::string::size_type pos = s.find(';') != std::string::npos)
  {
    const std::string firstNum(s.substr(0, pos));
    const std::string secondNum(s.substr(pos + 1, s.length() - pos));
    vector.first = stdStringToNumber<T>(firstNum);
    vector.second = stdStringToNumber<T>(secondNum);
  }
  return std::move(vector);
}

} // namespace utils

} // namespace ibrengine

#endif // UTILS_HPP
