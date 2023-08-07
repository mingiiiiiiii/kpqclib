add_executable(${LIB_NAME1}-main main.c)
target_link_libraries(${LIB_NAME1}-main ${LIB_NAME1})

add_executable(${LIB_NAME1}-testaim test_aim.c)
target_link_libraries(${LIB_NAME1}-testaim ${LIB_NAME1})

add_executable(${LIB_NAME1}-testtree test_tree.c)
target_link_libraries(${LIB_NAME1}-testtree ${LIB_NAME1})


add_executable(${LIB_NAME1}-testsign test_sign.c)
target_link_libraries(${LIB_NAME1}-testsign ${LIB_NAME1})








