
add_library(lrpc_79 OBJECT rbc_79_lrpc.c)
target_include_directories(lrpc_79 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(lrpc_79 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(lrpc_79 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(lrpc_79 PUBLIC ${CORE_79_DIR})
target_include_directories(lrpc_79 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
