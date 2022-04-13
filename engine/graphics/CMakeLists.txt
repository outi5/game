add_library(graphics
  graphics.cpp
  sprite.cpp
  animatedsprite.cpp
  )

target_compile_features(graphics PUBLIC cxx_std_17)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SDL2_INCLUDES})
target_link_libraries(graphics PUBLIC util PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
