set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(CONST_TEST_LIB_NAME1152 ${PROJECT_NAME}1152-const-test)
add_library(${CONST_TEST_LIB_NAME1152} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME1152} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME1152} PUBLIC CRYPTO_ALGNAME="NTRUPLUS1152_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME1152} PUBLIC NTRU_MODE=1152)

add_executable(${CONST_TEST_LIB_NAME1152}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME1152}-main ${CONST_TEST_LIB_NAME1152} ${LIB_NAME1152})


