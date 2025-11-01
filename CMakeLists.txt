cmake_minimum_required(VERSION 3.10)
project(MyGUI2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(MyGUI2 STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MyGUI2.cpp
)

target_include_directories(MyGUI2
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mipt-ded-zemax/include
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(MyGUI2 
                      PRIVATE SDL2::SDL2 SDL2_image::SDL2_image
                      PRIVATE SDL2_ttf::SDL2_ttf
                      PUBLIC  GeomLib)
