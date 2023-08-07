set(kat_srcs
    constant_time_test.c
)



# Rank-1 KEM
set(CONST_TEST_LIB_NAME3 ${PROJECT_NAME}192-constant-test)
add_library(${CONST_TEST_LIB_NAME3} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME3} PUBLIC CRYPTO_ALGNAME="PALOMA192_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME3} PUBLIC PALOMA_MODE=3)

add_executable(${CONST_TEST_LIB_NAME3}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME3}-main ${CONST_TEST_LIB_NAME3} ${LIB_NAME3})