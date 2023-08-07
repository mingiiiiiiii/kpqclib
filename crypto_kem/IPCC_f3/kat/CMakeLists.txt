set(kat_srcs
    PQCgenKAT_pke.c
)



# Rank-1 KEM
set(KAT_KEM_LIB_NAME3 ${PROJECT_NAME}3-kat-kem)
add_library(${KAT_KEM_LIB_NAME3} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME3} PUBLIC CRYPTO_ALGNAME="IPCC_f3")
target_compile_definitions(${KAT_KEM_LIB_NAME3} PUBLIC IPCC_f=3)

add_executable(${KAT_KEM_LIB_NAME3}-main PQCgenKAT_pke.c)
target_link_libraries(${KAT_KEM_LIB_NAME3}-main ${KAT_KEM_LIB_NAME3} ${LIB_NAME3})


