set(kat_srcs
    kat_kem.c
)



# Rank-1 KEM
set(CONST_TEST_LIB_NAME3 ${PROJECT_NAME}192-const-test)
add_library(${CONST_TEST_LIB_NAME3} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME3} PUBLIC CRYPTO_ALGNAME="TIGER192_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME3} PUBLIC TIGER_MODE=3)

add_executable(${CONST_TEST_LIB_NAME3}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME3}-main ${CONST_TEST_LIB_NAME3} ${LIB_NAME3})