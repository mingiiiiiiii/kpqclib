set(BENCH_NAME2 ${PROJECT_NAME}-72-46-benchmark)
add_executable(${BENCH_NAME2} speed.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_link_libraries(${BENCH_NAME2} ${LIB_NAME2})

