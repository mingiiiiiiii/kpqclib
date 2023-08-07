set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(KAT_KEM_LIB_NAME864 ${PROJECT_NAME}864-kat-kem)
add_library(${KAT_KEM_LIB_NAME864} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME864} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME864} PUBLIC CRYPTO_ALGNAME="NTRUPLUS864_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME864} PUBLIC NTRU_MODE=864)

add_executable(${KAT_KEM_LIB_NAME864}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME864}-main ${KAT_KEM_LIB_NAME864} ${LIB_NAME864})


