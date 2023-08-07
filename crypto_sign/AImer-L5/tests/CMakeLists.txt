add_executable(${LIB_NAME5}-main main.c)
target_link_libraries(${LIB_NAME5}-main ${LIB_NAME5})

add_executable(${LIB_NAME5}-testaim test_aim.c)
target_link_libraries(${LIB_NAME5}-testaim ${LIB_NAME5})

add_executable(${LIB_NAME5}-testtree test_tree.c)
target_link_libraries(${LIB_NAME5}-testtree ${LIB_NAME5})


add_executable(${LIB_NAME5}-testsign test_sign.c)
target_link_libraries(${LIB_NAME5}-testsign ${LIB_NAME5})








