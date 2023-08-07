cmake_minimum_required(VERSION 3.18)
project(MQS256 LANGUAGES C CXX) # CXX for the google test

#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MQS256_SRCS
  srcs/blas_comm.c
  srcs/blas_matrix_ref.c
  srcs/blas_matrix.c
  srcs/mqs_keypair_computation.c
  srcs/mqs_keypair.c
  srcs/mqs.c
  srcs/parallel_matrix_op.c
  srcs/sign.c
  srcs/utils_hash.c
  srcs/utils_prng.c
  srcs/utils.c
)


if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()


# find_package(OpenSSL REQUIRED)
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(MQS256-112-72_RNG SHARED ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_compile_options(MQS256-112-72_RNG PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME3 ${PROJECT_NAME}-112-72)
add_library(${LIB_NAME3} SHARED ${MQS256_SRCS})
#target_compile_definitions(${LIB_NAME2} PUBLIC MQS256_MODE=2)
target_compile_options(${LIB_NAME3} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME3} PUBLIC MQS256-112-72_RNG)
target_link_libraries(${LIB_NAME3} PUBLIC common)

add_subdirectory(test)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)