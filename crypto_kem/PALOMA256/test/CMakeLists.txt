include(GoogleTest)

add_executable(${LIB_NAME5}-main main.c)
target_link_libraries(${LIB_NAME5}-main ${LIB_NAME5})
target_compile_definitions(${LIB_NAME5}-main PUBLIC CRYPTO_ALGNAME="PALOMA256_KEM")
