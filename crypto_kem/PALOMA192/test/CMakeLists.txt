include(GoogleTest)

add_executable(${LIB_NAME3}-main main.c)
target_link_libraries(${LIB_NAME3}-main ${LIB_NAME3})
target_compile_definitions(${LIB_NAME3}-main PUBLIC CRYPTO_ALGNAME="PALOMA192_KEM")
