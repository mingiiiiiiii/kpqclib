set(kat_srcs
    kat_sign.c
)

# Rank-2 SIGN
set(CONST_TEST_LIB_NAME2 ${PROJECT_NAME}2-const-test)
add_library(${CONST_TEST_LIB_NAME2} SHARED ${kat_srcs})
target_include_directories(${CONST_TEST_LIB_NAME2} PUBLIC ../include)
target_compile_definitions(${CONST_TEST_LIB_NAME2} PUBLIC HAETAE_MODE=2)

add_executable(${CONST_TEST_LIB_NAME2}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME2}-main ${CONST_TEST_LIB_NAME2} ${LIB_NAME2})
