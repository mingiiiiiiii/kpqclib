
##### Global settings

cmake_minimum_required(VERSION 3.5)
project(rbc-lib)

set(rbc-lib_Version_MAJOR 0)
set(rbc-lib_Version_MINOR 1)



##### Build-dependant settings (from config.yml)

set(CORE_LAYER_IMPLEM "avx")

set(RBC_LIB_INSTALL_PATH /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin)
set(RBC_LIB_INSTALL_PATH_INC /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/mingiiiiiiii/KPQClean_0728/KPQClean/crypto_kem/Layered_ROLLO/Reference_implementation_221201/script/preprocessing/../../bin)



##### Compilation flags

if(CORE_LAYER_IMPLEM STREQUAL "avx")
  #set(CMAKE_C_FLAGS "-O3 -flto -march=skylake -mavx2 -mpclmul -msse4.2 -maes -std=c99 -pedantic -Wall -Wextra -Werror")
  set(CMAKE_C_FLAGS "-O3 -flto -mavx2 -mpclmul -msse4.2 -maes -std=c99 -pedantic -Wall -Wextra -g")
  #set(CMAKE_C_FLAGS "-O3 -mavx2 -mpclmul -msse4.2 -maes -std=c99 -pedantic -Wall -Wextra -Werror")
endif(CORE_LAYER_IMPLEM STREQUAL "avx")

if(CORE_LAYER_IMPLEM STREQUAL "c64")
  #set(CMAKE_C_FLAGS "-O3 -flto -march=skylake -std=c99 -pedantic -Wall -Wextra -Werror")
  set(CMAKE_C_FLAGS "-O3 -flto -std=c99 -pedantic -Wall -Wextra -Werror -g")
  #set(CMAKE_C_FLAGS "-O3 -std=c99 -pedantic -Wall -Wextra -Werror")
endif(CORE_LAYER_IMPLEM STREQUAL "c64")

if(CORE_LAYER_IMPLEM STREQUAL "c32")
  set(CMAKE_C_FLAGS "-O3 -flto -std=c99 -pedantic -Wall -Wextra -Werror -g")
endif(CORE_LAYER_IMPLEM STREQUAL "c32")


##### Compilation

set(SHA2_DIR                 ${CMAKE_CURRENT_SOURCE_DIR}/lib/sha2-portable)
set(FIPS202_DIR              ${CMAKE_CURRENT_SOURCE_DIR}/lib/fips202-portable)

if(CORE_LAYER_IMPLEM STREQUAL "avx")
  set(AES_DIR                ${CMAKE_CURRENT_SOURCE_DIR}/lib/aes-ni)
endif(CORE_LAYER_IMPLEM STREQUAL "avx")

if(CORE_LAYER_IMPLEM STREQUAL "c64")
  set(AES_DIR                ${CMAKE_CURRENT_SOURCE_DIR}/lib/aes-portable)
endif(CORE_LAYER_IMPLEM STREQUAL "c64")

if(CORE_LAYER_IMPLEM STREQUAL "c32")
  set(AES_DIR                ${CMAKE_CURRENT_SOURCE_DIR}/lib/aes-portable)
endif(CORE_LAYER_IMPLEM STREQUAL "c32")

set(RANDOM_SOURCE_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/lib/random_source)
set(RANDOMBYTES_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/lib/randombytes-pqclean)
set(SEEDEXPANDER_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/lib/seedexpander-pqclean)

set(SHA2_OPENSSL_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/lib/sha2-openssl)
set(RANDOMBYTES_NIST_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/lib/randombytes-nist)
set(SEEDEXPANDER_NIST_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/lib/seedexpander-nist)

set(CORE_67_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-67)
set(CORE_79_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-79)
set(CORE_97_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-97)
set(CORE_67_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-67)
set(CORE_79_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-79)
set(CORE_97_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/${CORE_LAYER_IMPLEM}/rbc-97)


set(LRPC_67_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-67)
set(LRPC_79_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-79)
set(LRPC_97_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-97)
set(LRPC_67_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-67)
set(LRPC_79_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-79)
set(LRPC_97_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/codes/lrpc-97)

set(ROLLOI128_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/rolloI128)
set(ROLLOI192_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/rolloI192)
set(ROLLOI256_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/rolloI256)
set(BIIX128_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/biix128)
set(BIIX192_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/biix192)
set(BIIX256_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/schemes/biix256)

add_subdirectory(${AES_DIR})
add_subdirectory(${SHA2_DIR})
add_subdirectory(${FIPS202_DIR})
add_subdirectory(${RANDOMBYTES_DIR})
add_subdirectory(${RANDOM_SOURCE_DIR})
add_subdirectory(${SEEDEXPANDER_DIR})

add_subdirectory(${SHA2_OPENSSL_DIR})
add_subdirectory(${RANDOMBYTES_NIST_DIR})
add_subdirectory(${SEEDEXPANDER_NIST_DIR})

add_subdirectory(src/core/${CORE_LAYER_IMPLEM}/rbc-67)
add_subdirectory(src/core/${CORE_LAYER_IMPLEM}/rbc-79)
add_subdirectory(src/core/${CORE_LAYER_IMPLEM}/rbc-97)

add_subdirectory(src/codes/lrpc-67)
add_subdirectory(src/codes/lrpc-79)
add_subdirectory(src/codes/lrpc-97)
add_subdirectory(src/schemes/rolloI128)
add_subdirectory(src/schemes/rolloI192)
add_subdirectory(src/schemes/rolloI256)
add_subdirectory(src/schemes/biix128)
add_subdirectory(src/schemes/biix192)
add_subdirectory(src/schemes/biix256)

add_library(rbc STATIC
  $<TARGET_OBJECTS:aes>
  $<TARGET_OBJECTS:sha2>
  $<TARGET_OBJECTS:fips202>
  $<TARGET_OBJECTS:random_source>
  $<TARGET_OBJECTS:randombytes>
  $<TARGET_OBJECTS:seedexpander>

  $<TARGET_OBJECTS:core_67>
  $<TARGET_OBJECTS:core_79>
  $<TARGET_OBJECTS:core_97>
  $<TARGET_OBJECTS:core_67>
  $<TARGET_OBJECTS:core_79>
  $<TARGET_OBJECTS:core_97>


  $<TARGET_OBJECTS:lrpc_67>
  $<TARGET_OBJECTS:lrpc_79>
  $<TARGET_OBJECTS:lrpc_97>
  $<TARGET_OBJECTS:lrpc_67>
  $<TARGET_OBJECTS:lrpc_79>
  $<TARGET_OBJECTS:lrpc_97>

  $<TARGET_OBJECTS:rolloI_128>
  $<TARGET_OBJECTS:rolloI_192>
  $<TARGET_OBJECTS:rolloI_256>
  $<TARGET_OBJECTS:biix_128>
  $<TARGET_OBJECTS:biix_192>
  $<TARGET_OBJECTS:biix_256>

)

add_library(rbc-nist STATIC
  $<TARGET_OBJECTS:fips202>
  $<TARGET_OBJECTS:sha2-openssl>
  $<TARGET_OBJECTS:random_source>
  $<TARGET_OBJECTS:randombytes-nist>
  $<TARGET_OBJECTS:seedexpander-nist>

  $<TARGET_OBJECTS:core_67>
  $<TARGET_OBJECTS:core_79>
  $<TARGET_OBJECTS:core_97>
  $<TARGET_OBJECTS:core_67>
  $<TARGET_OBJECTS:core_79>
  $<TARGET_OBJECTS:core_97>


  $<TARGET_OBJECTS:lrpc_67>
  $<TARGET_OBJECTS:lrpc_79>
  $<TARGET_OBJECTS:lrpc_97>
  $<TARGET_OBJECTS:lrpc_67>
  $<TARGET_OBJECTS:lrpc_79>
  $<TARGET_OBJECTS:lrpc_97>

  $<TARGET_OBJECTS:rolloI_128>
  $<TARGET_OBJECTS:rolloI_192>
  $<TARGET_OBJECTS:rolloI_256>
  $<TARGET_OBJECTS:biix_128>
  $<TARGET_OBJECTS:biix_192>
  $<TARGET_OBJECTS:biix_256>

)



##### Installation
set(RBC_LIB_SRC ${PROJECT_SOURCE_DIR}/src)
install(TARGETS rbc ARCHIVE DESTINATION ${RBC_LIB_INSTALL_PATH})
install(TARGETS rbc-nist ARCHIVE DESTINATION ${RBC_LIB_INSTALL_PATH})

install(FILES ${AES_DIR}/aes.h                                                    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${SHA2_DIR}/sha2.h                                                  DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${FIPS202_DIR}/fips202.h                                            DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RANDOM_SOURCE_DIR}/random_source.h                                              DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RANDOMBYTES_NIST_DIR}/randombytes.h                               DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${SEEDEXPANDER_DIR}/seedexpander.h                                  DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-67/rbc_67_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-79/rbc_79_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97.h        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_elt.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_vec.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_poly.h   DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_qre.h    DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/core/${CORE_LAYER_IMPLEM}/rbc-97/rbc_97_vspace.h DESTINATION ${RBC_LIB_INSTALL_PATH_INC})


install(FILES ${RBC_LIB_SRC}/codes/lrpc-67/rbc_67_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/codes/lrpc-79/rbc_79_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/codes/lrpc-97/rbc_97_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/codes/lrpc-67/rbc_67_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/codes/lrpc-79/rbc_79_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/codes/lrpc-97/rbc_97_lrpc.h             DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/rolloI128/rolloI_128_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI128/rolloI_128_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI128/rolloI_128_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI128/rolloI_128_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/rolloI192/rolloI_192_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI192/rolloI_192_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI192/rolloI_192_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI192/rolloI_192_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/rolloI256/rolloI_256_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI256/rolloI_256_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI256/rolloI_256_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/rolloI256/rolloI_256_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/biix128/biix_128_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix128/biix_128_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix128/biix_128_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix128/biix_128_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/biix192/biix_192_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix192/biix_192_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix192/biix_192_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix192/biix_192_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/schemes/biix256/biix_256_kem.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix256/biix_256_parsing.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix256/biix_256_types.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})
install(FILES ${RBC_LIB_SRC}/schemes/biix256/biix_256_parameters.h           DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

install(FILES ${RBC_LIB_SRC}/include/rbc.h                                        DESTINATION ${RBC_LIB_INSTALL_PATH_INC})

