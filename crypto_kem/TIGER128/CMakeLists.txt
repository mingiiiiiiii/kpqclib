cmake_minimum_required(VERSION 3.18)
project(TIGER LANGUAGES C CXX) # CXX for google test

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(srcs
    src/rng.c
    src/xef_ref.c
    src/TIGER_CPAPKE.c
    src/TIGER_CCAKEM.c
    src/kem.c
)

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -fPIC -Wall -Wextra -g)
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/kat)
include_directories(${CMAKE_SOURCE_DIR}/common)


add_library(TIGERRNG1 SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(TIGERRNG1 PRIVATE -O3 -fomit-frame-pointer -fPIC)

set(LIB_NAME1 ${PROJECT_NAME}128)
add_library(${LIB_NAME1} SHARED ${srcs})
target_compile_definitions(${LIB_NAME1} PUBLIC TIGER_MODE=1) # define TIGER_MODE 1
target_compile_options(${LIB_NAME1} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME1} PUBLIC TIGERRNG1)
target_link_libraries(${LIB_NAME1} PUBLIC common)

###########
add_subdirectory(kat)
add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)


