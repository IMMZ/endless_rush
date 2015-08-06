// todo: license

#include "utils.hpp"

#include <sstream>
#include <string>

namespace ibrengine
{

namespace utils
{

std::string extractFilenameFromPath(const std::string &filePath)
{
  // TODO: check, whether Tiled uses '/' under Windows.
  int fileNameStart = filePath.find_last_of('/') + 1;
  return filePath.substr(fileNameStart, filePath.length() - fileNameStart);
}

void splitString(const std::string &str, char splitChar, bool includeEmpty, std::vector<std::string> &result)
{
  std::string token;
  for (char c: str)
  {
    if (c != splitChar)
    {
      token += c;
    }
    else if (c== splitChar)
    {
      result.push_back(token);
      token.clear();
    }
  }
  result.push_back(token);
}

int stdStringToInt(const std::string &str)
{
  std::stringstream ss; int value;
  ss << str; ss >> value;
  return value;
}

std::string IntToStdString(int i)
{
  std::stringstream ss; std::string value;
  ss << i; ss >> value;
  return value;
}

float stdStringToFloat(const std::string &str)
{
  std::stringstream ss; float value;
  ss << str; ss >> value;
  return value;
}

std::string floatToStdString(float f)
{
  std::stringstream ss; std::string value;
  ss << f; ss >> value;
  return value;
}

sf::Color hexColorToSFMLColor(const std::string &hexColor)
{
  std::stringstream ss;
  int r, g, b;
  ss << std::hex << hexColor.substr(0, 2); ss >> r;
  ss.clear(); ss.str("");
  ss << std::hex << hexColor.substr(2, 2); ss >> g;
  ss.clear(); ss.str("");
  ss << std::hex << hexColor.substr(4, 2); ss >> b;
  ss.clear(); ss.str("");
  return sf::Color(r, g, b);
}

} // namespace utils

} // namespace ibrengine
