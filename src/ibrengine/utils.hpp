// todo: license

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>

namespace ibrengine
{

namespace utils
{

std::string extractFilenameFromPath(const std::string &filePath);
void splitString(const std::string &str, char splitChar, bool includeEmpty, std::vector<std::string> &result);
int stdStringToInt(const std::string &str);
std::string IntToStdString(int i);
float stdStringToFloat(const std::string &str);
std::string floatToStdString(float f);
sf::Color hexColorToSFMLColor(const std::string &hexColor);

} // namespace utils

} // namespace ibrengine

#endif // UTILS_HPP
