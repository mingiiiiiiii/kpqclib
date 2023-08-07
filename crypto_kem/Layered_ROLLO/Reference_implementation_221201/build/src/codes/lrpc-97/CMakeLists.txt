
add_library(lrpc_97 OBJECT rbc_97_lrpc.c)
target_include_directories(lrpc_97 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(lrpc_97 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(lrpc_97 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(lrpc_97 PUBLIC ${CORE_97_DIR})
target_include_directories(lrpc_97 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
