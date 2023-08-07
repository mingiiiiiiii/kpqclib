set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME3 ${PROJECT_NAME}3-kat-sign)
add_library(${KAT_SIGN_LIB_NAME3} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME3}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME3}-main ${KAT_SIGN_LIB_NAME3} ${LIB_NAME3} nccsign3_fips202 common)
#target_link_libraries(${KAT_SIGN_LIB_NAME2}-main PUBLIC common)

set(KAT_SIGN_LIB_NAME3aes ${PROJECT_NAME}3aes-kat-sign)
add_library(${KAT_SIGN_LIB_NAME3aes} SHARED ${kat_srcs})

add_executable(${KAT_SIGN_LIB_NAME3aes}-main PQCgenKAT_sign.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${KAT_SIGN_LIB_NAME3aes}-main ${KAT_SIGN_LIB_NAME3aes} ${LIB_NAME3aes} nccsign3_fips202 nccsign3_aes256ctr common)

#target_link_libraries(${KAT_SIGN_LIB_NAME2}aes-main PUBLIC common)