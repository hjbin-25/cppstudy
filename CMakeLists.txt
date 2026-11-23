cmake_minimum_required(VERSION 3.20)
project(cppstudy CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        # -std=gnu++20 대신 -std=c++20

add_compile_options(-Wall -Wextra -g -fno-omit-frame-pointer)

# AddressSanitizer + UBSan (끄려면 -DSTUDY_SANITIZE=OFF)
option(STUDY_SANITIZE "Build with -fsanitize=address,undefined" ON)
if(STUDY_SANITIZE)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# common/tracer.h 를 #include "tracer.h" 로 쓸 수 있게
include_directories(${CMAKE_SOURCE_DIR}/common)

add_subdirectory(s1)
add_subdirectory(s2)