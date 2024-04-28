cmake_minimum_required(VERSION 3.16)

project(
  uspiral
  DESCRIPTION "Ulam Spiral Visualization"
  LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE uspiral.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC graphics spiral)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${US_BIN_DIR})
