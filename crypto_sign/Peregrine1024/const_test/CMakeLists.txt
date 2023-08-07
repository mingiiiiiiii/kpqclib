set(CONST_TEST_LIB_NAME1024 ${PROJECT_NAME}1024-const-test)
add_executable(${CONST_TEST_LIB_NAME1024}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME1024}-main ${LIB_NAME1024})

