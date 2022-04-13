project(engine)

# set path to SDL include directory
set(SDL2_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include")

# set path to SDL and SDL_Image libraries
if(APPLE)
   set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/libSDL2.dylib")
   set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/libSDL2_image.dylib")
elseif(WIN32)
   set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/bin/SDL2.dll")
   set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/bin/SDL2_image.dll")
else()
    find_library(SDL2_LIBRARIES NAMES libSDL2 libSDL2.so libSDL2.a)
    find_library(SDL2_IMAGE_LIBRARIES NAMES libSDL2_image libSDL2_image.so libSDL2_image.a)
endif()

message(STATUS "Found SDL2 = ${SDL2_LIBRARIES}")
message(STATUS "Found SDL2_image = ${SDL2_IMAGE_LIBRARIES}")

add_subdirectory(util)
add_subdirectory(graphics)
add_subdirectory(map)
add_subdirectory(input)

add_library(engine
  action.cpp
  actor.cpp
  hero.cpp
  herotype.cpp
  monster.cpp
  monstertype.cpp
  weapon.cpp
  actors.cpp
  camera.cpp
  event.cpp
  events.cpp
  settings.cpp
  engine.cpp)

target_compile_features(engine PUBLIC cxx_std_17)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC util graphics map input)
