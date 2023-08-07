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
  set(C_FLAGS -O3 -fomit-frame-pointer -fPIC -Wall -Wextra -g)
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/kat)
include_directories(${CMAKE_SOURCE_DIR}/common)


add_library(IPCCRNG4 SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(IPCCRNG4 PRIVATE -O3 -fomit-frame-pointer -fPIC)

set(LIB_NAME4 ${PROJECT_NAME}4)
add_library(${LIB_NAME4} SHARED ${srcs})
target_compile_definitions(${LIB_NAME4} PUBLIC IPCC_f=4) # define IPCC_f 4
target_compile_options(${LIB_NAME4} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME4} PUBLIC IPCCRNG4)
target_link_libraries(${LIB_NAME4} PUBLIC common)

###########
add_subdirectory(kat)
add_subdirectory(test)
add_subdirectory(benchmark)