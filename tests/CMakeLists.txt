find_package(GTest REQUIRED)

add_executable(unit_tests_matrix unit/test_matrix.cpp)
target_include_directories(unit_tests_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(unit_tests_matrix PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME unit_all_matrix COMMAND unit_tests_matrix)

add_executable(unit_tests_vector unit/test_myvector.cpp)
target_include_directories(unit_tests_vector PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(unit_tests_vector PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME unit_all_vector COMMAND unit_tests_vector)

add_executable(e2e
  ${CMAKE_CURRENT_SOURCE_DIR}/e2e_runner.cpp
  ${CMAKE_SOURCE_DIR}/src/runner.cpp
)
target_include_directories(e2e PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(e2e PRIVATE matrix)

target_compile_definitions(e2e PRIVATE TESTS_DIR="${CMAKE_SOURCE_DIR}/tests")
