set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(CONST_TEST_LIB_NAME2 ${PROJECT_NAME}2-const-test)
add_library(${CONST_TEST_LIB_NAME2} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME2}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME2}-main ${CONST_TEST_LIB_NAME2} ${LIB_NAME2} nccsign2_fips202 common)
#target_link_libraries(${CONST_TEST_LIB_NAME2}-main PUBLIC common)

set(CONST_TEST_LIB_NAME2aes ${PROJECT_NAME}2aes-const-test)
add_library(${CONST_TEST_LIB_NAME2aes} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME2aes}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME2aes}-main ${CONST_TEST_LIB_NAME2aes} ${LIB_NAME2aes} nccsign2_fips202 nccsign2_aes256ctr common)

#target_link_libraries(${CONST_TEST_LIB_NAME2}aes-main PUBLIC common)