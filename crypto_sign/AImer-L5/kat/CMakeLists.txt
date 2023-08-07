set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME5 ${PROJECT_NAME}5-kat-sign)
add_library(${KAT_SIGN_LIB_NAME5} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME5}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME5}-main ${KAT_SIGN_LIB_NAME5} ${LIB_NAME5})
