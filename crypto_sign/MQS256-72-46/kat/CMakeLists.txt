set(KAT_SIGN_LIB_NAME2 ${PROJECT_NAME}-72-46)
add_executable(${KAT_SIGN_LIB_NAME2}-kat-sign-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME2}-kat-sign-main ${LIB_NAME2})

