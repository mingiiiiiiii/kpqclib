
add_library(core_79 OBJECT rbc_79_elt.c rbc_79_vec.c rbc_79_poly.c rbc_79_vspace.c rbc_79_qre.c)
target_include_directories(core_79 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(core_79 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(core_79 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(core_79 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
