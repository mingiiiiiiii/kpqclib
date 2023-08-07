set(kat_srcs
    constant_time_test.c
)



# Rank-1 KEM
set(CONST_TEST_LIB_NAME1 ${PROJECT_NAME}128-constant-test)
add_library(${CONST_TEST_LIB_NAME1} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME1} PUBLIC CRYPTO_ALGNAME="PALOMA128_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME1} PUBLIC PALOMA_MODE=1)

add_executable(${CONST_TEST_LIB_NAME1}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME1}-main ${CONST_TEST_LIB_NAME1} ${LIB_NAME1})