cmake_minimum_required(VERSION 3.4.0)
project(easytree_test)

get_filename_component(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
set(CATCH "${TOP_DIR}/contrib/Catch")

include_directories(
  ${TOP_DIR}/include
  ${CATCH}/include
)

set(TEST_SOURCES
  easytree.cpp)

add_executable(easytree_test
  ${TEST_SOURCES})

target_compile_definitions(easytree_test PUBLIC "CATCH_CONFIG_MAIN" "CATCH_CONFIG_COLOUR_NONE")
add_test(CommonTests easytree_test)
