
add_library(biix_256 OBJECT biix_256_parsing.c biix_256_kem.c)

target_include_directories(biix_256 PUBLIC ${SHA2_DIR})
target_include_directories(biix_256 PUBLIC ${FIPS202_DIR})
target_include_directories(biix_256 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(biix_256 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(biix_256 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(biix_256 PUBLIC ${CORE_97_DIR})
target_include_directories(biix_256 PUBLIC ${LRPC_97_DIR})
target_include_directories(biix_256 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
