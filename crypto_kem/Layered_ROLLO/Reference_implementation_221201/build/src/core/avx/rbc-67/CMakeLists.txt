
add_library(core_67 OBJECT rbc_67_elt.c rbc_67_vec.c rbc_67_poly.c rbc_67_vspace.c rbc_67_qre.c)
target_include_directories(core_67 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(core_67 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(core_67 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(core_67 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
