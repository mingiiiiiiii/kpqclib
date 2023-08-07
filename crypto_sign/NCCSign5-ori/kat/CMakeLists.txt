set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME5 ${PROJECT_NAME}5-kat-sign)
add_library(${KAT_SIGN_LIB_NAME5} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME5}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME5}-main ${KAT_SIGN_LIB_NAME5} ${LIB_NAME5} nccsign5_fips202 common)
#target_link_libraries(${KAT_SIGN_LIB_NAME2}-main PUBLIC common)

set(KAT_SIGN_LIB_NAME5aes ${PROJECT_NAME}5aes-kat-sign)
add_library(${KAT_SIGN_LIB_NAME5aes} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME5aes}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME5aes}-main ${KAT_SIGN_LIB_NAME5aes} ${LIB_NAME5aes} nccsign5_fips202 nccsign5_aes256ctr common)

#target_link_libraries(${KAT_SIGN_LIB_NAME2}aes-main PUBLIC common)