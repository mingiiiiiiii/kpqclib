add_executable(${LIB_NAME3}-main main.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_compile_definitions(${LIB_NAME3} PUBLIC MQS256_MODE=3)
target_link_libraries(${LIB_NAME3}-main ${LIB_NAME3})
