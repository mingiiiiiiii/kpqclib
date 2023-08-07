set(kat_srcs
    katrng.c
    # PQCgenKAT_sign.c
    #${CMAKE_SOURCE_DIR}/common/aes.c
)
#message(${CMAKE_SOURCE_DIR})
# Rank-2 SIGN
set(KAT_SIGN_LIB_NAME1024 ${PROJECT_NAME}-kat-sign)
add_library(${KAT_SIGN_LIB_NAME1024} SHARED ${kat_srcs})
target_include_directories(${KAT_SIGN_LIB_NAME1024} PUBLIC ../include)

add_executable(${KAT_SIGN_LIB_NAME1024}-main PQCgenKAT_sign.c)
target_link_libraries(${KAT_SIGN_LIB_NAME1024}-main ${KAT_SIGN_LIB_NAME1024} ${LIB_NAME1024})
target_link_libraries(${KAT_SIGN_LIB_NAME1024}-main ${KAT_SIGN_LIB_NAME1024} m) 
