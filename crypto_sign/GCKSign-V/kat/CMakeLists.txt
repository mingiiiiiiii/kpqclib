set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME5 ${PROJECT_NAME}-V-kat-sign)
add_library(${KAT_SIGN_LIB_NAME5} SHARED ${kat_srcs})
target_include_directories(${KAT_SIGN_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${KAT_SIGN_LIB_NAME5} PUBLIC GCKSign_MODE=5)

add_executable(${KAT_SIGN_LIB_NAME5}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME5}-main ${KAT_SIGN_LIB_NAME5} ${LIB_NAME5})
