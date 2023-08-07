set(kat_srcs
    kat_kem.c
)


# Rank-2 KEM
set(KAT_KEM_LIB_NAME1 ${PROJECT_NAME}1-kat-kem)
add_library(${KAT_KEM_LIB_NAME1} SHARED ${kat_srcs})
target_include_directories(${KAT_KEM_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${KAT_KEM_LIB_NAME1} PUBLIC CRYPTO_ALGNAME="SMAUG1_KEM")
target_compile_definitions(${KAT_KEM_LIB_NAME1} PUBLIC SMAUG_MODE=1)

add_executable(${KAT_KEM_LIB_NAME1}-main PQCgenKAT_kem.c)
target_link_libraries(${KAT_KEM_LIB_NAME1}-main ${KAT_KEM_LIB_NAME1} ${LIB_NAME1})


