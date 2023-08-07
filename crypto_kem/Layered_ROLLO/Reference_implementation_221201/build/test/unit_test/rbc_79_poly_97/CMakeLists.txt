add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(test_rbc_79_poly_97 test_rbc_79_poly_97.cpp)

target_link_libraries(test_rbc_79_poly_97 PUBLIC rbc)
target_link_libraries(test_rbc_79_poly_97 PUBLIC OpenSSL::Crypto)
target_link_libraries(test_rbc_79_poly_97 PRIVATE ${NTL_LIB})
target_link_libraries(test_rbc_79_poly_97 PRIVATE ${GMP_LIB})

target_include_directories(test_rbc_79_poly_97 PUBLIC ${RBC_LIB_INCLUDE})
target_include_directories(test_rbc_79_poly_97 PUBLIC ${CMAKE_SOURCE_DIR}/../../../lib/minunit)

