cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(linear_algebra)

include_directories(${CMAKE_SOURCE_DIR}/include)

set (SOURCES
  src/vector.cpp
  src/matrix.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_executable(test test/test.cpp)

target_link_libraries(test ${PROJECT_NAME})
