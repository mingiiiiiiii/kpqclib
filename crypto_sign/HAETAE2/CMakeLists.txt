cmake_minimum_required(VERSION 3.18)
project(haetae LANGUAGES C CXX) # CXX for the google test

#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HAETAE_SRCS
  src/poly.c
  src/ntt.c
  src/reduce.c
  src/polyvec.c
  src/polymat.c
  src/rounding.c
  src/polydbl.c
  src/sampler.c
  src/packing.c
  src/sign.c
)

set(HAETAE_FIPS202_SRCS
  ${HAETAE_SRCS}
  src/symmetric-shake.c
)

set(FIPS202_SRCS src/fips202.c)

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(haetae2_fips202 SHARED ${FIPS202_SRCS})
add_library(haetae2_RNG SHARED ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_compile_options(haetae2_RNG PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME2 ${PROJECT_NAME}2)
add_library(${LIB_NAME2} SHARED ${HAETAE_FIPS202_SRCS})
target_compile_definitions(${LIB_NAME2} PUBLIC HAETAE_MODE=2)
target_compile_options(${LIB_NAME2} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME2} INTERFACE haetae2_fips202 m)
target_link_libraries(${LIB_NAME2} PUBLIC haetae2_RNG)
target_link_libraries(${LIB_NAME2} PUBLIC common)

add_subdirectory(test)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)