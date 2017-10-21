cmake_minimum_required(VERSION 3.0)
set(PROJECT ten_more_bullets)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 11)

# Find SDL2
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

set(SOURCES 
    src/game.cpp
    src/gun.cpp
    src/key_press.cpp
    src/main.cpp
    src/rectangle.cpp
    )

set(HEADERS
    include/bullet.h
    include/color.h
    include/game.h
    include/gun.h
    include/key_press.h
    include/rectangle.h
    )

add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT} PRIVATE include ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT} ${SDL2_LIBRARIES} ${EXTRA_LIBS})

# Add a run step
add_custom_target(run ./${PROJECT} DEPENDS ${PROJECT})
