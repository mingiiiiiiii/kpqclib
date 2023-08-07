cmake_minimum_required(VERSION 3.18)
project(EnhpqsigRM LANGUAGES C CXX) # CXX for the google test

#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(pqsigRM_SRCS
  src/common.c
  src/keypair.c
  src/matrix.c
  src/nearest_vector.c
  src/open.c
  src/rm.c
  src/rng.c
  src/sign.c
)


if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()

include_directories(include)
include_directories(kat)
include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(EnhpqsigRM-613-RNG SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(EnhpqsigRM-613-RNG PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME5 ${PROJECT_NAME}-613)
add_library(${LIB_NAME5} SHARED ${pqsigRM_SRCS})
target_compile_definitions(${LIB_NAME5} PUBLIC pqsigRM_MODE=5)
target_compile_options(${LIB_NAME5} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME5} PUBLIC EnhpqsigRM-613-RNG)
target_link_libraries(${LIB_NAME5} PUBLIC common)

add_subdirectory(tests)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)