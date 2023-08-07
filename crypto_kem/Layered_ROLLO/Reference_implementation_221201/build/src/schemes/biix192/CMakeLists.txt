
add_library(biix_192 OBJECT biix_192_parsing.c biix_192_kem.c)

target_include_directories(biix_192 PUBLIC ${SHA2_DIR})
target_include_directories(biix_192 PUBLIC ${FIPS202_DIR})
target_include_directories(biix_192 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(biix_192 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(biix_192 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(biix_192 PUBLIC ${CORE_79_DIR})
target_include_directories(biix_192 PUBLIC ${LRPC_79_DIR})
target_include_directories(biix_192 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
