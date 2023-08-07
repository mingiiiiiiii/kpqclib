set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME3 ${PROJECT_NAME}3-kat-sign)
add_library(${KAT_SIGN_LIB_NAME3} SHARED ${kat_srcs})
target_include_directories(${KAT_SIGN_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${KAT_SIGN_LIB_NAME3} PUBLIC HAETAE_MODE=3)

add_executable(${KAT_SIGN_LIB_NAME3}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME3}-main ${KAT_SIGN_LIB_NAME3} ${LIB_NAME3})
