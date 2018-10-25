cmake_minimum_required(VERSION 2.8.12)
project(example)


if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
    message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

link_directories(/opt/opencv/lib64)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

add_executable(main convert_cifar10.cpp utils.cpp)
target_link_libraries(main PRIVATE tcmalloc glog ${OPENCV_LIBRARIES})
target_include_directories(main PRIVATE ${OPENCV_INCLUDE_DIRS})
target_compile_options(main PRIVATE ${OPENCV_CFLAGS_OTHER})
