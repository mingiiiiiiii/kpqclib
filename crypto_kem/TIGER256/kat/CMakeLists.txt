set(kat_srcs
    kat_kem.c
)



# Rank-3 KEM
set(KAT_KEM_LIB_NAME5 ${PROJECT_NAME}256-kat-kem)
add_library(${KAT_KEM_LIB_NAME5} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME5} PUBLIC CRYPTO_ALGNAME="TIGER256_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME5} PUBLIC TIGER_MODE=5)

add_executable(${KAT_KEM_LIB_NAME5}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME5}-main ${KAT_KEM_LIB_NAME5} ${LIB_NAME5})