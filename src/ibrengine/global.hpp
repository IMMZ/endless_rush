// TODO: license text

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////////
// Macroses.
/////////////////////////////////////////////////////////////////////////////////////////////
#define DISABLE_COPY(ClassName)\
  ClassName(const ClassName &obj) = delete;\
  ClassName& operator=(const ClassName &obj) = delete;

#define DISABLE_MOVE(ClassName)\
  ClassName(ClassName &&obj) = delete;\
  ClassName& operator=(ClassName &&obj) = delete;

namespace ibrengine
{

// Types.
using Point = std::pair<int, int>;
using PositionI = std::pair<int, int>;
using PositionF = std::pair<float, float>;
using LinearVelocity = std::pair<float, float>;

namespace internal
{

// Functions.

template<typename T, typename ... Ts>
std::unique_ptr<T> make_unique(Ts&& ... params)
{
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

}

}

#endif // GLOBAL_HPP
