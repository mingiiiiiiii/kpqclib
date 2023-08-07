cmake_minimum_required(VERSION 3.18)
project(Solmae1024 LANGUAGES C CXX) # CXX for the google test

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -lm -g)
endif()


#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_LINKER "clang")


set(SOLMAE1024_SRCS
  src/common.c
  src/falcon_keygen.c
  src/fips202.c
  src/nist.c
  src/poly.c
  src/randombytes.c
  src/samplerZ.c
  src/sign.c
  src/vrfy.c
  src/codec.c
  src/fft.c
  src/fpr.c
  src/keygen.c
  src/normaldist.c
  src/precomp.c
  src/rng.c
  src/shake.c
  src/test_dist.c
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/common)


add_library(SOLMAE1024_RNG SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(SOLMAE1024_RNG PRIVATE -O3 -fomit-frame-pointer -fPIC -lm)

# HAETAE 2
set(LIB_NAME1024 ${PROJECT_NAME})
add_library(${LIB_NAME1024} SHARED ${SOLMAE1024_SRCS})
# target_compile_definitions(${LIB_NAME512} PUBLIC )
target_compile_options(${LIB_NAME1024} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME1024} PUBLIC common)
target_link_libraries(${LIB_NAME1024} PUBLIC SOLMAE1024_RNG)


add_subdirectory(test)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)









