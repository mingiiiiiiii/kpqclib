cmake_minimum_required(VERSION 3.18)
project(nccsign-ori LANGUAGES C CXX) # CXX for the google test

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()


#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(NIMS_SRCS
  src/sign.c
  src/packing.c
  src/poly.c
  src/reduce.c
  src/rounding.c
  src/randombytes.c
)

include_directories(include)
include_directories(aes)
include_directories(fips)
include_directories(${CMAKE_SOURCE_DIR}/common)

set(FIPS202_SRCS fips/fips202.c)
add_library(nccsign2_fips202 SHARED ${FIPS202_SRCS})
add_library(nccsign2_aes256ctr SHARED ${PROJECT_SOURCE_DIR}/aes/aes256ctr.c)
target_compile_options(nccsign2_aes256ctr PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME2 ${PROJECT_NAME}2)
add_library(${LIB_NAME2} SHARED ${NIMS_SRCS} fips/symmetric-shake.c)
target_compile_definitions(${LIB_NAME2} PUBLIC NIMS_MODE=2)
target_compile_options(${LIB_NAME2} PRIVATE ${C_FLAGS})
#target_link_libraries(${LIB_NAME2} PUBLIC nccsign2_aes256ctr nccsign2_fips202)

# HAETAE 2
set(LIB_NAME2aes ${PROJECT_NAME}2aes)
add_library(${LIB_NAME2aes} SHARED ${NIMS_SRCS} aes/symmetric-aes.c)
target_compile_definitions(${LIB_NAME2aes} PUBLIC NIMS_MODE=2 NIMS_USE_AES)
target_compile_options(${LIB_NAME2aes} PRIVATE ${C_FLAGS})
#target_link_libraries(${LIB_NAME2} PUBLIC nccsign2_aes256ctr nccsign2_fips202)

add_subdirectory(test)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(metamorphic)
add_subdirectory(const_test)








