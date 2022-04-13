add_library(input
  input.cpp
  )

target_compile_features(input PUBLIC cxx_std_17)
target_include_directories(input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SDL2_INCLUDES})
target_link_libraries(input PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

