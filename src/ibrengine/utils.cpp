// todo: license

#include "utils.hpp"

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

bool stringToBool(const sf::String &str)
{
  if (str == "Y" || str == "y"
      || str == "Yes" || str == "yes"
      || str == "1"
      || str == "True" || str == "true")
    return true;

  return false;
}

} // namespace utils

} // namespace ibrengine
