add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(test_rbc_79_poly_43 test_rbc_79_poly_43.cpp)

target_link_libraries(test_rbc_79_poly_43 PUBLIC rbc)
target_link_libraries(test_rbc_79_poly_43 PUBLIC OpenSSL::Crypto)
target_link_libraries(test_rbc_79_poly_43 PRIVATE ${NTL_LIB})
target_link_libraries(test_rbc_79_poly_43 PRIVATE ${GMP_LIB})

target_include_directories(test_rbc_79_poly_43 PUBLIC ${RBC_LIB_INCLUDE})
target_include_directories(test_rbc_79_poly_43 PUBLIC ${CMAKE_SOURCE_DIR}/../../../lib/minunit)

