set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME1 ${PROJECT_NAME}1-kat-sign)
add_library(${KAT_SIGN_LIB_NAME1} SHARED ${kat_srcs})
target_compile_definitions(${KAT_SIGN_LIB_NAME1} PUBLIC AIMER_MODE=1)

add_executable(${KAT_SIGN_LIB_NAME1}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME1}-main ${KAT_SIGN_LIB_NAME1} ${LIB_NAME1})
