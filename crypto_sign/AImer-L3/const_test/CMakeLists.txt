set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(CONST_TEST_LIB_NAME3 ${PROJECT_NAME}3-const-test)
add_library(${CONST_TEST_LIB_NAME3} SHARED ${kat_srcs})
target_compile_definitions(${CONST_TEST_LIB_NAME3} PUBLIC AIMER_MODE=3)

add_executable(${CONST_TEST_LIB_NAME3}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME3}-main ${CONST_TEST_LIB_NAME3} ${LIB_NAME3})
