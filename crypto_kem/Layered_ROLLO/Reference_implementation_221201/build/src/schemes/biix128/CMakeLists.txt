
add_library(biix_128 OBJECT biix_128_parsing.c biix_128_kem.c)

target_include_directories(biix_128 PUBLIC ${SHA2_DIR})
target_include_directories(biix_128 PUBLIC ${FIPS202_DIR})
target_include_directories(biix_128 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(biix_128 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(biix_128 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(biix_128 PUBLIC ${CORE_67_DIR})
target_include_directories(biix_128 PUBLIC ${LRPC_67_DIR})
target_include_directories(biix_128 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
