add_library(actors
  heros.cpp
  monsters.cpp
  )

target_include_directories(actors PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(actors PUBLIC engine actions weapons)
