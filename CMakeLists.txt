cmake_minimum_required(VERSION 3.1)

project(volt_ecs
  DESCRIPTION "An Entity-Component-System for C++20"
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

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")
endif()

# variables
set(VOLT_ECS_TARGET_NAME  ${PROJECT_NAME})
set(VOLT_ECS_INCLUDE_DIR  src/)
set(VOLT_ECS_SOURCE_DIR  src/)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH cmake/)

file(GLOB_RECURSE SRC "${VOLT_ECS_SOURCE_DIR}*.cc")

# create project
add_library(
  ${VOLT_ECS_TARGET_NAME} 
  SHARED
  ${SRC}
)

## compiler flags

# setup include hierarchy
target_include_directories(${VOLT_ECS_TARGET_NAME} INTERFACE ${VOLT_ECS_INCLUDE_DIR})
target_link_libraries(${VOLT_ECS_TARGET_NAME})

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(ext/Catch2)
    add_subdirectory(tests)
endif()
