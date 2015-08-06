// todo: license

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

namespace ibrengine
{

class Exception
{
public:
  explicit Exception(const std::string &what);
  virtual ~Exception();

  const std::string& what() const;

private:
  std::string mWhat;
};

} // namespace ibrengine

#endif // EXCEPTION_HPP
