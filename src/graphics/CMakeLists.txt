cmake_minimum_required(VERSION 3.16)

find_package(Curses REQUIRED)

project(
  graphics
  DESCRIPTION "Screen Drawing Controls"
  LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE screen.cpp)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CURSES_INCLUDE_DIR}
  PUBLIC ${US_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
