add_library(map
  builder.cpp
  decorator.cpp
  door.cpp
  room.cpp
  tile.cpp
  fov.cpp
  fog.cpp
  pathfinding.cpp
  dungeon.cpp
  )

target_compile_features(map PUBLIC cxx_std_17)
target_include_directories(map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(map PUBLIC util graphics)
