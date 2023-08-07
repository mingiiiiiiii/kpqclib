set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(CONST_TEST_LIB_NAME5 ${PROJECT_NAME}5-const-test)
add_library(${CONST_TEST_LIB_NAME5} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME5}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME5}-main ${CONST_TEST_LIB_NAME5} ${LIB_NAME5} nccsign2_fips202 common)
#target_link_libraries(${CONST_TEST_LIB_NAME5}-main PUBLIC common)

set(CONST_TEST_LIB_NAME5aes ${PROJECT_NAME}5aes-const-test)
add_library(${CONST_TEST_LIB_NAME5aes} SHARED ${kat_srcs})

add_executable(${CONST_TEST_LIB_NAME5aes}-main constant_time_test.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${CONST_TEST_LIB_NAME5aes}-main ${CONST_TEST_LIB_NAME5aes} ${LIB_NAME5aes} nccsign2_fips202 nccsign2_aes256ctr common)

#target_link_libraries(${CONST_TEST_LIB_NAME5}aes-main PUBLIC common)