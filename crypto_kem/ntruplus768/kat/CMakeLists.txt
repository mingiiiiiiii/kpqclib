set(kat_srcs
    kat_kem.c
)

# Rank-2 KEM
set(KAT_KEM_LIB_NAME768 ${PROJECT_NAME}768-kat-kem)
add_library(${KAT_KEM_LIB_NAME768} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME768} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME768} PUBLIC CRYPTO_ALGNAME="NTRUPLUS768_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME768} PUBLIC NTRU_MODE=768)

add_executable(${KAT_KEM_LIB_NAME768}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME768}-main ${KAT_KEM_LIB_NAME768} ${LIB_NAME768})


