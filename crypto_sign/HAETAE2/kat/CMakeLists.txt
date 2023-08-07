set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME2 ${PROJECT_NAME}2-kat-sign)
add_library(${KAT_SIGN_LIB_NAME2} SHARED ${kat_srcs})
target_include_directories(${KAT_SIGN_LIB_NAME2} PUBLIC ../include)
target_compile_definitions(${KAT_SIGN_LIB_NAME2} PUBLIC HAETAE_MODE=2)

add_executable(${KAT_SIGN_LIB_NAME2}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME2}-main ${KAT_SIGN_LIB_NAME2} ${LIB_NAME2})
