set(CONST_TEST_LIB_NAME5 ${PROJECT_NAME}-148-96)
add_executable(${CONST_TEST_LIB_NAME5}-const-test-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME5}-const-test-main ${LIB_NAME5})

