set(CONST_TEST_LIB_NAME3 ${PROJECT_NAME}-112-72)
add_executable(${CONST_TEST_LIB_NAME3}-const-test-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME3}-const-test-main ${LIB_NAME3})

