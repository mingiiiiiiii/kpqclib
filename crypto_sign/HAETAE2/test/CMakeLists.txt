add_executable(${LIB_NAME2}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME2}-main ${LIB_NAME2})
