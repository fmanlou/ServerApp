include(cmake/utils.cmake)

# SOURCE
file(GLOB_RECURSE SRC_LIST ${CMAKE_SOURCE_DIR}/lib/*.cpp)

# SOURCE Include
list_subdirectories(APP_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/)

# MOCK
file(GLOB_RECURSE MOCK_SRC_LIST ${CMAKE_SOURCE_DIR}/tests/mock/*.cpp)

# MOCK Include
list_subdirectories(MOCK_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/tests/mock)

# For All Test
find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address --coverage")

# For Unit Test
set(unit_test_name unitTest)
file(GLOB_RECURSE TEST_SRC_LIST ${CMAKE_SOURCE_DIR}/tests/unit/*.cpp)
add_executable(${unit_test_name} ${SRC_LIST} ${TEST_SRC_LIST} ${MOCK_SRC_LIST})
target_link_libraries(${unit_test_name} Catch2::Catch2WithMain proto)
target_include_directories(${unit_test_name} PUBLIC ${APP_INCLUDE_DIRECTORIES}
                                                    ${MOCK_INCLUDE_DIRECTORIES})
catch_discover_tests(${unit_test_name})

# For Benchmark
set(benchmark_name benchmark)
file(GLOB_RECURSE BENCHMARK_SRC_LIST ${CMAKE_SOURCE_DIR}/tests/benchmark/*.cpp)
add_executable(${benchmark_name} ${BENCHMARK_SRC_LIST})
target_link_libraries(${benchmark_name} Catch2::Catch2WithMain)
target_include_directories(${benchmark_name} PUBLIC ${APP_INCLUDE_DIRECTORIES})
