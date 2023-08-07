set(BENCH_NAME3 ${PROJECT_NAME}-112-72-benchmark)
add_executable(${BENCH_NAME3} speed.c ${PROJECT_SOURCE_DIR}/srcs/rng.c)
target_link_libraries(${BENCH_NAME3} ${LIB_NAME3})

