set(kat_srcs
    PQCgenKAT_pke.c
)



# Rank-1 KEM
set(KAT_KEM_LIB_NAME4 ${PROJECT_NAME}4-kat-kem)
add_library(${KAT_KEM_LIB_NAME4} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME4} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME4} PUBLIC CRYPTO_ALGNAME="IPCC_f4")
target_compile_definitions(${KAT_KEM_LIB_NAME4} PUBLIC IPCC_f=4)

add_executable(${KAT_KEM_LIB_NAME4}-main PQCgenKAT_pke.c)
target_link_libraries(${KAT_KEM_LIB_NAME4}-main ${KAT_KEM_LIB_NAME4} ${LIB_NAME4})


