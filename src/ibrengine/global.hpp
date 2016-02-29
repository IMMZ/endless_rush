// TODO: license text

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <memory>

// Macroses.
#define DISABLE_COPY(Class) \
  Class(const Class &obj) = delete;\
  Class& operator=(const Class &obj) = delete;

namespace ibrengine
{

// Types.
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
