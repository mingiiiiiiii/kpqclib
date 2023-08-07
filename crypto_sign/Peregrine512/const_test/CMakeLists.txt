set(CONST_TEST_LIB_NAME512 ${PROJECT_NAME}512-const-test)
add_executable(${CONST_TEST_LIB_NAME512}-main constant_time_test.c)
target_link_libraries(${CONST_TEST_LIB_NAME512}-main ${LIB_NAME512})

