project(ibrengine)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

find_package(SFML 2.1 COMPONENTS system window graphics)

set(SRC
  animation.cpp
  animatableobjectt.cpp
  complexshape.cpp
  drawableobjectt.cpp
  exception.cpp
  layer.cpp
  map.cpp
  maploadexception.cpp
  mapobject.cpp
  maprenderer.cpp
  object.cpp
  objectlayer.cpp
  simpleshape.cpp
  tilelayer.cpp
  tileset.cpp
  tmxloader.cpp
  utils.cpp
  xmlparseexception.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../../lib")
include_directories("../rapidxml-1.13")
include_directories(${SFML_INCLUDE_DIR}/SFML)
add_library(ibrengine STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})