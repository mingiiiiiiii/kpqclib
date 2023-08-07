add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(test_cst_rbc_97_elt test_rbc_97_elt.c)

target_link_libraries(test_cst_rbc_97_elt PUBLIC rbc)
target_link_libraries(test_cst_rbc_97_elt PUBLIC OpenSSL::Crypto)
target_link_libraries(test_cst_rbc_97_elt PRIVATE ${NTL_LIB})
target_link_libraries(test_cst_rbc_97_elt PRIVATE ${GMP_LIB})

target_include_directories(test_cst_rbc_97_elt PUBLIC ${RBC_LIB_INCLUDE})
