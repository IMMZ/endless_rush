project(game)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++11)

find_package(SFML 2.1 COMPONENTS system window graphics audio)

set(SRC
  game.cpp 
  gameobject.cpp
  gameresources.cpp
  gameworld.cpp
  ingamestate.cpp
  introstate.cpp
  levelloadingstate.cpp
  maincharacter.cpp
  menustate.cpp
  mortalobject.cpp
  pausestate.cpp
  settings.cpp
  titlesstate.cpp
  main.cpp)

set(CMAKE_BINARY_OUTPUT_DIRECTORY "../../bin")
include_directories(
  ${SFML_INCLUDE_DIR}/SFML
  "../ibrengine"
  "../rapidxml-1.13"
  "/opt/box2d/include")
link_directories(
  "/home/ibram/Work/games/lib"
  "/opt/box2d/lib")
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ibrengine Box2D)
