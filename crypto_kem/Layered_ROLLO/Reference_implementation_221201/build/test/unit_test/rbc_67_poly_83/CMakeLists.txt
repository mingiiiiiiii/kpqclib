add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(test_rbc_67_poly_83 test_rbc_67_poly_83.cpp)

target_link_libraries(test_rbc_67_poly_83 PUBLIC rbc)
target_link_libraries(test_rbc_67_poly_83 PUBLIC OpenSSL::Crypto)
target_link_libraries(test_rbc_67_poly_83 PRIVATE ${NTL_LIB})
target_link_libraries(test_rbc_67_poly_83 PRIVATE ${GMP_LIB})

target_include_directories(test_rbc_67_poly_83 PUBLIC ${RBC_LIB_INCLUDE})
target_include_directories(test_rbc_67_poly_83 PUBLIC ${CMAKE_SOURCE_DIR}/../../../lib/minunit)

