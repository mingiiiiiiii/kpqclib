add_executable(${LIB_NAME3}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME3}-main ${LIB_NAME3})
