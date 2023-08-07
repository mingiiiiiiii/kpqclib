set(KAT_SIGN_LIB_NAME512 ${PROJECT_NAME}512)
add_executable(${KAT_SIGN_LIB_NAME512}-kat-sign-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME512}-kat-sign-main ${KAT_SIGN_LIB_NAME512} ${LIB_NAME512})

