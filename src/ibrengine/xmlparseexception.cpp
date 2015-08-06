// todo: license

#include "xmlparseexception.hpp"

namespace ibrengine
{

XmlParseException::XmlParseException(const std::string &what, const std::string &where):
  Exception(what),
  mWhere(where)
{
}

const std::string& XmlParseException::where() const
{
  return mWhere;
}

} // namespace ibrengine
