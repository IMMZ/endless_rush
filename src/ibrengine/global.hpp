// TODO: license text

#ifndef IBRENGINE_GLOBAL_HPP
#define IBRENGINE_GLOBAL_HPP

#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////////
// Macroses.
/////////////////////////////////////////////////////////////////////////////////////////////
#define ENABLE_DEFAULT_COPY(ClassName)\
  ClassName(const ClassName &obj) = default;\
  ClassName& operator=(const ClassName &obj) = default;

#define DISABLE_COPY(ClassName)\
  ClassName(const ClassName &obj) = delete;\
  ClassName& operator=(const ClassName &obj) = delete;

#define ENABLE_DEFAULT_MOVE(ClassName)\
  ClassName(ClassName &&obj) = default;\
  ClassName& operator=(ClassName &&obj) = default;

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

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&& ...params)
{
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

template<typename From, typename To>
std::unique_ptr<To> dynamic_unique_pointer_cast(std::unique_ptr<From> &&ptr)
{
  return std::unique_ptr<To>(dynamic_cast<To*>(ptr.release()));
}

} // namespace internal

} // namespace ibrengine

#endif // IBRENGINE_GLOBAL_HPP
