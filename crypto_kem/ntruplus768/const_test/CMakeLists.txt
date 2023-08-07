set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(CONST_TEST_LIB_NAME768 ${PROJECT_NAME}768-const-test)
add_library(${CONST_TEST_LIB_NAME768} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME768} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME768} PUBLIC CRYPTO_ALGNAME="NTRUPLUS768_CONST")
target_compile_definitions(${CONST_TEST_LIB_NAME768} PUBLIC NTRU_MODE=768)

add_executable(${CONST_TEST_LIB_NAME768}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME768}-main ${CONST_TEST_LIB_NAME768} ${LIB_NAME768})


