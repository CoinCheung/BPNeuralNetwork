cmake_minimum_required(VERSION 2.8.12)
project(example)


## compile options
if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
    message ("CMAKE_CXX_FLAGS is: ${CMAKE_CXX_FLAGS}")
endif (CMAKE_COMPILER_IS_GNUCXX)

## include directories
include_directories(
    Matrix
    Layers
    Optimizer
    Math
    utils
    )

## link directories
link_directories(/opt/opencv/lib64)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

## source files
file(GLOB SRC_LAYERS "Layers/*.cpp")
file(GLOB SRC_OPTIMIZER "Optimizer/*.cpp")
file(GLOB SRC_MATRIX "Matrix/*.cpp")
file(GLOB SRC_UTILS "utils/*.cpp")
file(GLOB SRC_ROOT "*.cpp")
set(SRCS ${SRC_LAYERS} ${SRC_OPTIMIZER} ${SRC_MATRIX} ${SRC_UTILS} ${SRC_ROOT})
foreach(f ${SRCS})
    message(${f})
endforeach(f)


## compile executable
add_executable(main ${SRCS})
target_link_libraries(main PRIVATE tcmalloc ${OPENCV_LIBRARIES})
target_include_directories(main PRIVATE ${OPENCV_INCLUDE_DIRS})
target_compile_options(main PRIVATE ${OPENCV_CFLAGS_OTHER})
