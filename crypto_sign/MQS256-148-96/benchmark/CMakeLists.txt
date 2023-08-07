set(BENCH_NAME5 ${PROJECT_NAME}-148-96-benchmark)
add_executable(${BENCH_NAME5} speed.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_link_libraries(${BENCH_NAME5} ${LIB_NAME5})

