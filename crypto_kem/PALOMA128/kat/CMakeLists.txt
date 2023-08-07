set(kat_srcs
    KAT.c
)



# Rank-1 KEM
set(KAT_KEM_LIB_NAME1 ${PROJECT_NAME}128-kat-kem)
add_library(${KAT_KEM_LIB_NAME1} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME1} PUBLIC CRYPTO_ALGNAME="PALOMA128_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME1} PUBLIC PALOMA_MODE=1)

add_executable(${KAT_KEM_LIB_NAME1}-main KAT.c)
target_link_libraries(${KAT_KEM_LIB_NAME1}-main ${KAT_KEM_LIB_NAME1} ${LIB_NAME1})