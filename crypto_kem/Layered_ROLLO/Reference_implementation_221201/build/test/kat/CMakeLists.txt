cmake_minimum_required(VERSION 3.5)
project(kat)

set(RBC_LIB_SOURCE /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin/librbc-nist.a)
set(RBC_LIB_INCLUDE /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin)

add_subdirectory(rolloI128)
add_subdirectory(rolloI192)
add_subdirectory(rolloI256)
add_subdirectory(biix128)
add_subdirectory(biix192)
add_subdirectory(biix256)

