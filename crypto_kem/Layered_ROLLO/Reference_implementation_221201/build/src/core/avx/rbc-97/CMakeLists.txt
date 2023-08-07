
add_library(core_97 OBJECT rbc_97_elt.c rbc_97_vec.c rbc_97_poly.c rbc_97_vspace.c rbc_97_qre.c)
target_include_directories(core_97 PUBLIC ${RANDOMBYTES_DIR})
target_include_directories(core_97 PUBLIC ${SEEDEXPANDER_DIR})
target_include_directories(core_97 PUBLIC ${RANDOM_SOURCE_DIR})
target_include_directories(core_97 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
