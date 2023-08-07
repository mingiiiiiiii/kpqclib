set(kat_srcs
    katrng.c
    # PQCgenKAT_sign.c
    #${CMAKE_SOURCE_DIR}/common/aes.c
)
#message(${CMAKE_SOURCE_DIR})
# Rank-2 SIGN
set(CONST_TEST_LIB_NAME1024 ${PROJECT_NAME}-const-test)
add_library(${CONST_TEST_LIB_NAME1024} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME1024} PUBLIC ../include)

add_executable(${CONST_TEST_LIB_NAME1024}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME1024}-main ${CONST_TEST_LIB_NAME1024} ${LIB_NAME1024})
target_link_libraries(${CONST_TEST_LIB_NAME1024}-main ${CONST_TEST_LIB_NAME1024} m) 
