include(GoogleTest)

add_executable(${LIB_NAME1}-main main.c)
target_link_libraries(${LIB_NAME1}-main ${LIB_NAME1})
target_compile_definitions(${LIB_NAME1}-main PUBLIC CRYPTO_ALGNAME="PALOMA128_KEM")
