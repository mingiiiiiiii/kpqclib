set(CONST_TEST_LIB_NAME2 ${PROJECT_NAME}-72-46)
add_executable(${CONST_TEST_LIB_NAME2}-const-test-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME2}-const-test-main ${LIB_NAME2})

