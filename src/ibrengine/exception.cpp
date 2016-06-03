// todo: license

#include "exception.hpp"

namespace ibrengine
{

Exception::Exception(const std::string &what):
  mWhat(what)
{
}

const std::string& Exception::what() const
{
  return mWhat;
}

} // namespace ibrengine
