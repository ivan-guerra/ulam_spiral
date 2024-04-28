cmake_minimum_required(VERSION 3.16)

set(TESTNAME spiral_test)

add_executable(${TESTNAME} ${TESTNAME}.cpp)

target_link_libraries(${TESTNAME} PRIVATE gtest_main spiral)

gtest_discover_tests(${TESTNAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

set_target_properties(${TESTNAME} PROPERTIES FOLDER test)
