set(KAT_SIGN_LIB_NAME3 ${PROJECT_NAME}-112-72)
add_executable(${KAT_SIGN_LIB_NAME3}-kat-sign-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME3}-kat-sign-main ${LIB_NAME3})

