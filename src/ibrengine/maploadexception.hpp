// todo: license

#ifndef MAPLOADEXCEPTION_HPP
#define MAPLOADEXCEPTION_HPP

#include "exception.hpp"

namespace ibrengine
{

class MapLoadException: public Exception
{
public:
  explicit MapLoadException(const std::string &what);
};

} // namespace ibrengine

#endif // MAPLOADEXCEPTION_HPP
