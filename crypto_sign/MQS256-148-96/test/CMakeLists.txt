add_executable(${LIB_NAME5}-main main.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_compile_definitions(${LIB_NAME5} PUBLIC MQS256_MODE=5)
target_link_libraries(${LIB_NAME5}-main ${LIB_NAME5})
