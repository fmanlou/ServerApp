cmake_minimum_required(VERSION 3.22)
project(ServerApp)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include(cmake/build.cmake)

add_subdirectory(lib/proto)

add_executable(ServerApp main.cpp ${SRC_LIST})
target_link_libraries(ServerApp PUBLIC proto)
target_include_directories(ServerApp PUBLIC ${APP_INCLUDE_DIRECTORIES})
