add_executable(${LIB_NAME3}-main main.c)
target_link_libraries(${LIB_NAME3}-main ${LIB_NAME3})

add_executable(${LIB_NAME3}-testaim test_aim.c)
target_link_libraries(${LIB_NAME3}-testaim ${LIB_NAME3})

add_executable(${LIB_NAME3}-testtree test_tree.c)
target_link_libraries(${LIB_NAME3}-testtree ${LIB_NAME3})


add_executable(${LIB_NAME3}-testsign test_sign.c)
target_link_libraries(${LIB_NAME3}-testsign ${LIB_NAME3})








