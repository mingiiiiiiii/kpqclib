add_executable(${LIB_NAME2}-main main.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_compile_definitions(${LIB_NAME2} PUBLIC MQS256_MODE=2)
target_link_libraries(${LIB_NAME2}-main ${LIB_NAME2})
