cmake_minimum_required(VERSION 3.18)
project(Almer-l LANGUAGES C CXX) # CXX for the google test

#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AIMER_SRCS
  #src/aim_common.c
  #src/aim128.c
  #src/aim192.c
  src/aim256.c
  src/aimer_instances.c
  src/aimer_internal.c
  src/aimer.c
  src/api.c
  src/hash.c
  src/rng.c
  src/tree.c
  field/field256.c
)
set(AIMER_FIPS202_SRCS
  shake/KeccakHash.c 
  shake/KeccakSponge.c 
  shake/KeccakP-1600-opt64.c
)

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()

include_directories(include)
include_directories(field)
include_directories(shake)
include_directories(${CMAKE_SOURCE_DIR}/common)

add_library(aimer5_fips202 SHARED ${AIMER_FIPS202_SRCS})
add_library(aimer5_RNG SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(aimer5_RNG PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME5 ${PROJECT_NAME}5)
add_library(${LIB_NAME5} SHARED ${AIMER_SRCS})
target_compile_definitions(${LIB_NAME5} PUBLIC AIMER_MODE=5)
target_compile_options(${LIB_NAME5} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME5} INTERFACE aimer5_fips202 m)
target_link_libraries(${LIB_NAME5} PUBLIC aimer5_RNG)
target_link_libraries(${LIB_NAME5} PUBLIC common)

add_subdirectory(tests)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)
