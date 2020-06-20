cmake_minimum_required(VERSION 3.1)

project(volt_ecs
  DESCRIPTION "An Entity-Component-System for C++17"
  LANGUAGES CXX)

# includes

# only enable tests if this is the project being make
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)
endif()

# variables
set(VOLT_ECS_TARGET_NAME  ${PROJECT_NAME})
set(VOLT_ECS_INCLUDE_DIR  include/)

# create project
add_library(${VOLT_ECS_TARGET_NAME} INTERFACE)

# compiler flags
target_compile_features(${VOLT_ECS_TARGET_NAME} INTERFACE cxx_std_17)

# setup include hierarchy
target_include_directories(${VOLT_ECS_TARGET_NAME} INTERFACE ${VOLT_ECS_INCLUDE_DIR})

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
