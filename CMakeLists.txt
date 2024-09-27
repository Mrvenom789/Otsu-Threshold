cmake_minimum_required(VERSION 3.0)
project(otsu_threshold VERSION 0.1)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(otsu_threshold otsu.cpp)

target_link_libraries(otsu_threshold ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)