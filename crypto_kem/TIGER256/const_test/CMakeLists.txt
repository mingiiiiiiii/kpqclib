set(kat_srcs
    kat_kem.c
)



# Rank-1 KEM
set(CONST_TEST_LIB_NAME5 ${PROJECT_NAME}256-const-test)
add_library(${CONST_TEST_LIB_NAME5} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME5} PUBLIC CRYPTO_ALGNAME="TIGER256_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME5} PUBLIC TIGER_MODE=5)

add_executable(${CONST_TEST_LIB_NAME5}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME5}-main ${CONST_TEST_LIB_NAME5} ${LIB_NAME5})