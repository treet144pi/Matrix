cmake_minimum_required(VERSION 3.16)
project(TreeSearchAVL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(vector INTERFACE)
target_include_directories(vector INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_library(matrix INTERFACE)
target_include_directories(matrix INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(matrix INTERFACE vector)

add_executable(funcdet src/funcdet.cpp src/runner.cpp)
target_link_libraries(funcdet PRIVATE matrix)
target_include_directories(funcdet PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(benchdet src/benchdet.cpp src/runner.cpp)
target_link_libraries(benchdet PRIVATE matrix)
target_include_directories(benchdet PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(CTest)
if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
