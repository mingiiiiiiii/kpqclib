add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(test_cst_rbc_97_poly_113 test_rbc_97_poly_113.c)

target_link_libraries(test_cst_rbc_97_poly_113 PUBLIC rbc)
target_link_libraries(test_cst_rbc_97_poly_113 PUBLIC OpenSSL::Crypto)
target_link_libraries(test_cst_rbc_97_poly_113 PRIVATE ${NTL_LIB})
target_link_libraries(test_cst_rbc_97_poly_113 PRIVATE ${GMP_LIB})

target_include_directories(test_cst_rbc_97_poly_113 PUBLIC ${RBC_LIB_INCLUDE})

