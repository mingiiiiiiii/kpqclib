
add_library(lrpc_67 OBJECT rbc_67_lrpc.c)
target_include_directories(lrpc_67 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(lrpc_67 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(lrpc_67 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(lrpc_67 PUBLIC ${CORE_67_DIR})
target_include_directories(lrpc_67 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
