cmake_minimum_required(VERSION 3.16)

find_package(PNG REQUIRED)
find_package(Boost REQUIRED)

project(
  spiral
  DESCRIPTION "Ulam Spiral Generator and Image Utils"
  LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE image.cpp spiral.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${US_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost PNG::PNG)
