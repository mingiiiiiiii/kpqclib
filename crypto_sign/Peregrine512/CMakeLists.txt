cmake_minimum_required(VERSION 3.18)
project(Peregrine LANGUAGES C CXX) # CXX for the google test

if(MSVC)
  set(C_FLAGS /nologo /O2 /W4 /wd4146 /wd4244)
else()
  set(C_FLAGS -O3 -fomit-frame-pointer -Wall -Wextra -Wpedantic -g)
endif()


#enable_testing() # Enables running `ctest`

set(CMAKE_C_STANDARD 11)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_LINKER "clang")


set(PEREGRINE_SRCS
  src/codec.c
  src/common.c
  src/fft.c
  src/fpr.c
  src/keygen.c
  src/shake.c
  src/sign.c
  src/vrfy.c
  src/rng.c
)

include_directories(include)


add_library(Peregrine512_RNG SHARED ${PROJECT_SOURCE_DIR}/src/rng.c)
target_compile_options(Peregrine512_RNG PRIVATE -O3 -fomit-frame-pointer -fPIC)

# HAETAE 2
set(LIB_NAME512 ${PROJECT_NAME}512)
add_library(${LIB_NAME512} SHARED ${PEREGRINE_SRCS})
target_compile_definitions(${LIB_NAME512} PUBLIC Peregrine_MODE=9)
target_compile_options(${LIB_NAME512} PRIVATE ${C_FLAGS})
target_link_libraries(${LIB_NAME512} m)
#target_link_libraries(${LIB_NAME2} PUBLIC nccsign2_aes256ctr)

add_subdirectory(test)
add_subdirectory(kat)
add_subdirectory(benchmark)
add_subdirectory(const_test)









