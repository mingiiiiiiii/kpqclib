set(KAT_SIGN_LIB_NAME1024 ${PROJECT_NAME}1024)
add_executable(${KAT_SIGN_LIB_NAME1024}-kat-sign-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME1024}-kat-sign-main ${KAT_SIGN_LIB_NAME1024} ${LIB_NAME1024})

