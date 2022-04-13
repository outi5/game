add_library(util
  randomness.cpp
  grid.cpp
  timer.cpp
  vec.cpp
  )

target_compile_features(util PUBLIC cxx_std_17)
target_compile_options(util PUBLIC -ggdb -std=c++17)
target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
