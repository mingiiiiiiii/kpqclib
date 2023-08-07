set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME2 ${PROJECT_NAME}2-kat-sign)
add_library(${KAT_SIGN_LIB_NAME2} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME2}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME2}-main ${KAT_SIGN_LIB_NAME2} ${LIB_NAME2} nccsign2_fips202 common)
#target_link_libraries(${KAT_SIGN_LIB_NAME2}-main PUBLIC common)

set(KAT_SIGN_LIB_NAME2aes ${PROJECT_NAME}2aes-kat-sign)
add_library(${KAT_SIGN_LIB_NAME2aes} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME2aes}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME2aes}-main ${KAT_SIGN_LIB_NAME2aes} ${LIB_NAME2aes} nccsign2_fips202 nccsign2_aes256ctr common)

#target_link_libraries(${KAT_SIGN_LIB_NAME2}aes-main PUBLIC common)