set(kat_srcs
    KAT.c
)



# Rank-1 KEM
set(KAT_KEM_LIB_NAME3 ${PROJECT_NAME}192-kat-kem)
add_library(${KAT_KEM_LIB_NAME3} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME3} PUBLIC CRYPTO_ALGNAME="PALOMA192_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME3} PUBLIC PALOMA_MODE=3)

add_executable(${KAT_KEM_LIB_NAME3}-main KAT.c)
target_link_libraries(${KAT_KEM_LIB_NAME3}-main ${KAT_KEM_LIB_NAME3} ${LIB_NAME3})