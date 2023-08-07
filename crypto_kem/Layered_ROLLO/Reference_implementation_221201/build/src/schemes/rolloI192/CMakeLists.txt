
add_library(rolloI_192 OBJECT rolloI_192_parsing.c rolloI_192_kem.c)

target_include_directories(rolloI_192 PUBLIC ${SHA2_DIR})
target_include_directories(rolloI_192 PUBLIC ${FIPS202_DIR})
target_include_directories(rolloI_192 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(rolloI_192 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(rolloI_192 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(rolloI_192 PUBLIC ${CORE_79_DIR})
target_include_directories(rolloI_192 PUBLIC ${LRPC_79_DIR})
target_include_directories(rolloI_192 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
