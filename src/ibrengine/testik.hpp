/*
======CASES TO USE======

1. Use in game.
2. Use in TmxLoader.

======CASES TO USE======

======ОБЩИЙ ПРИНЦИП ПАРСИНГА ОБЪЕКТА======
- Переделать ObjectDirector:
  - добавить 'void addObject(Object &obj);'
  - удалить createObjects() и isFlagSet() + HandledTypes
======ОБЩИЙ ПРИНЦИП ПАРСИНГА ОБЪЕКТА======

*/



#ifndef TESTIK_HPP
#define TESTIK_HPP

#include <memory>

#include "animatableobjectt.hpp"
#include "animation.hpp"
#include "drawableobjectt.hpp"
#include "mapobject.hpp"
#include "object.hpp"
#include "objectlayer.hpp"

#include <SFML/System/Time.hpp>

namespace ibrengine
{

class PhysicalObjectt: public Object
{
public:
  PhysicalObjectt(MapObject &director):
    Object(director, Object::Type::Physical)
  {
  }
};

} // namespace ibrengine

#endif // TESTIK_HPP
