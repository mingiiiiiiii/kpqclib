set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(CONST_TEST_LIB_NAME3 ${PROJECT_NAME}3-const-test)
add_library(${CONST_TEST_LIB_NAME3} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME3}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME3}-main ${CONST_TEST_LIB_NAME3} ${LIB_NAME3} nccsign2_fips202 common)
#target_link_libraries(${CONST_TEST_LIB_NAME3}-main PUBLIC common)

set(CONST_TEST_LIB_NAME3aes ${PROJECT_NAME}3aes-const-test)
add_library(${CONST_TEST_LIB_NAME3aes} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME3aes}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME3aes}-main ${CONST_TEST_LIB_NAME3aes} ${LIB_NAME3aes} nccsign2_fips202 nccsign2_aes256ctr common)

#target_link_libraries(${CONST_TEST_LIB_NAME3}aes-main PUBLIC common)