project(ibrengine)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

find_package(SFML 2.1 COMPONENTS system window graphics)

set(SRC
  animation.cpp
  animatableobject.cpp
  audiomanager.cpp
  box.cpp
  chainshape.cpp
  circle.cpp
  debugdraw.cpp
  drawableobject.cpp
  exception.cpp
  imagelayer.cpp
  layer.cpp
  map.cpp
  maploadexception.cpp
  mapobject.cpp
  maprenderer.cpp
  object.cpp
  objectlayer.cpp
  physicobject.cpp
  physicworld.cpp
  polygonshape.cpp
  shape.cpp
  tilelayer.cpp
  tileset.cpp
  tmxloader.cpp
  utils.cpp
  xmlparseexception.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../../lib")
include_directories("../rapidxml-1.13")
include_directories(${SFML_INCLUDE_DIR}/SFML)
include_directories(/opt/box2d/include)
add_library(ibrengine STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})