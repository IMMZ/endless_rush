// todo: license

#ifndef XMLPARSEEXCEPTION_HPP
#define XMLPARSEEXCEPTION_HPP

#include "exception.hpp"

namespace ibrengine
{

class XmlParseException: public Exception
{
public:
  XmlParseException(const std::string &what, const std::string &where);

  const std::string& where() const;

private:
  const std::string mWhere;
};

} // namespace ibrengine

#endif // XMLPARSEEXCEPTION_HPP
