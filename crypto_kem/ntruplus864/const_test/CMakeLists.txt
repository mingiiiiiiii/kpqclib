set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(CONST_TEST_LIB_NAME864 ${PROJECT_NAME}864-const-test)
add_library(${CONST_TEST_LIB_NAME864} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME864} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME864} PUBLIC CRYPTO_ALGNAME="NTRUPLUS864_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME864} PUBLIC NTRU_MODE=864)

add_executable(${CONST_TEST_LIB_NAME864}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME864}-main ${CONST_TEST_LIB_NAME864} ${LIB_NAME864})


