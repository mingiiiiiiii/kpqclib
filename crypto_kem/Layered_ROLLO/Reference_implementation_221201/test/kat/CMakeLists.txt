cmake_minimum_required(VERSION 3.5)
project(kat)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-expansion-to-defined -g")

set(RBC_LIB_SOURCE CONFIG_LIB_DIR/librbc-nist.a)
set(RBC_LIB_INCLUDE CONFIG_LIB_DIR/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY CONFIG_LIB_DIR)



{TEMPLATING_CMAKE_ADD_SUBDIRECTORY}
