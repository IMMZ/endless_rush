// todo: license

#include "maploadexception.hpp"

namespace ibrengine
{

MapLoadException::MapLoadException(const std::string &what):
  Exception(what)
{
}

} // namespace ibrengine
