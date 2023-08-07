set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(KAT_KEM_LIB_NAME576 ${PROJECT_NAME}576-kat-kem)
add_library(${KAT_KEM_LIB_NAME576} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME576} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME576} PUBLIC CRYPTO_ALGNAME="NTRUPLUS576_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME576} PUBLIC NTRU_MODE=576)

add_executable(${KAT_KEM_LIB_NAME576}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME576}-main ${KAT_KEM_LIB_NAME576} ${LIB_NAME576})


