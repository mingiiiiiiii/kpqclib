cmake_minimum_required(VERSION 3.5)
project(unit_tests)

set(RBC_LIB_SOURCE /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin/librbc.a)
set(RBC_LIB_INCLUDE /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-expansion-to-defined")

find_package(OpenSSL REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake)
find_library(NTL_LIB ntl)
find_library(GMP_LIB gmp)
include_directories(/usr/local/include)

add_subdirectory(rbc_67_elt)
add_subdirectory(rbc_67_vspace)
add_subdirectory(rbc_67_poly_83)
add_subdirectory(rbc_79_elt)
add_subdirectory(rbc_79_vspace)
add_subdirectory(rbc_79_poly_97)
add_subdirectory(rbc_97_elt)
add_subdirectory(rbc_97_vspace)
add_subdirectory(rbc_97_poly_113)
add_subdirectory(rbc_67_poly_37)
add_subdirectory(rbc_79_poly_43)
add_subdirectory(rbc_97_poly_53)

