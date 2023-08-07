cmake_minimum_required(VERSION 3.18)
project(IPCC LANGUAGES C CXX) # CXX for google test

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(srcs
    src/pke.c
    src/Keygen.c
    src/Encryption.c
    src/MultiEnc.c
    src/Decryption.c
    src/rng.c
    src/verify.c
    src/fips202.c
)


if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -g -fomit-frame-pointer -fPIC -Wall -Wextra)
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/kat)
include_directories(${CMAKE_SOURCE_DIR}/common)


add_library(IPCCRNG1 SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(IPCCRNG1 PRIVATE -O3 -fomit-frame-pointer -fPIC)

set(LIB_NAME1 ${PROJECT_NAME}1)
add_library(${LIB_NAME1} SHARED ${srcs})
target_compile_definitions(${LIB_NAME1} PUBLIC IPCC_f=1) # define IPCC_f 1
target_compile_options(${LIB_NAME1} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME1} PUBLIC IPCCRNG1)
target_link_libraries(${LIB_NAME1} PUBLIC common)

###########
add_subdirectory(kat)
add_subdirectory(test)
add_subdirectory(benchmark)