cmake_minimum_required(VERSION 3.18)
project(PALOMA LANGUAGES C CXX) # CXX for google test

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(srcs
    src/gf_table_gen.c
    src/gf.c 
    src/gfpoly.c
    src/goppa_instance.c
    src/keygen.c 
    src/mat_mul.c
    src/common.c
    src/lsh.c
    src/lsh512.c
    src/encap.c
    src/decap.c
    src/PALOMA.c
    src/rng.c
)

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -fPIC -Wall -Wextra -g)
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/kat)
include_directories(${CMAKE_SOURCE_DIR}/common)


add_library(PALOMARNG3 SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(PALOMARNG3 PRIVATE -O3 -fomit-frame-pointer -fPIC)

set(LIB_NAME3 ${PROJECT_NAME}192)
add_library(${LIB_NAME3} SHARED ${srcs})
target_compile_definitions(${LIB_NAME3} PUBLIC PALOMA_MODE=3) # define PALOMA_MODE 3
target_compile_options(${LIB_NAME3} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME3} PUBLIC PALOMARNG3)
target_link_libraries(${LIB_NAME3} PUBLIC common)

###########
add_subdirectory(kat)
add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)



