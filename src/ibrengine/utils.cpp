// todo: license

#include "utils.hpp"

namespace ibrengine
{

namespace utils
{

std::string extractFilenameFromPath(const std::string &filePath)
{
  // TODO: check, whether Tiled uses '/' under Windows.
  const int fileNameStart = filePath.find_last_of('/') + 1;
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

  /*
   * We cannot use uint8_t with r, g and b here because of uint8_t is
   * typedef'ed as unsigned char and stringstream operator>>() just
   * copies first character from two 'hexColor.substr(*, 2)' which goes
   * to unexpected number - characters' code not converted hex => uint8_t value.
   */
  uint16_t r = 0, g = 0, b = 0;
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
  return (str == "Y" or str == "y"
    or str == "Yes" or str == "yes"
    or str == "1"
    or str == "True" or str == "true") ? true : false;
}

} // namespace utils

} // namespace ibrengine
