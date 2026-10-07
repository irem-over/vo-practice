cmake_minimum_required(VERSION 3.16)
project(vo_practice CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)

foreach(target hello show_sequence fast_corners klt_tracking benchmark)
  add_executable(${target} src/${target}.cpp)
  target_include_directories(${target} PRIVATE ${OpenCV_INCLUDE_DIRS})
  target_link_libraries(${target} PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)
endforeach()