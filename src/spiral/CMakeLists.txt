cmake_minimum_required(VERSION 3.16)

project(
  spiral
  DESCRIPTION "Ulam Spiral Generator"
  LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE spiral.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${US_INCLUDE_DIR})
