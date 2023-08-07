set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(KAT_KEM_LIB_NAME1152 ${PROJECT_NAME}1152-kat-kem)
add_library(${KAT_KEM_LIB_NAME1152} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME1152} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME1152} PUBLIC CRYPTO_ALGNAME="NTRUPLUS1152_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME1152} PUBLIC NTRU_MODE=1152)

add_executable(${KAT_KEM_LIB_NAME1152}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME1152}-main ${KAT_KEM_LIB_NAME1152} ${LIB_NAME1152})


