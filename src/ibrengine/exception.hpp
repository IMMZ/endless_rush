// todo: license

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "global.hpp"

#include <string>

namespace ibrengine
{

class Exception
{
public:
  ENABLE_DEFAULT_MOVE(Exception);

  explicit Exception(const std::string &what);
  virtual ~Exception() = default;

  const std::string& what() const;

private:
  std::string mWhat;
};

} // namespace ibrengine

#endif // EXCEPTION_HPP
