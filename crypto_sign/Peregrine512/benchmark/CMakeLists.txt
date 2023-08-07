set(BENCH_NAME ${PROJECT_NAME}512-benchmark)
add_executable(${BENCH_NAME} speed.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${BENCH_NAME} ${LIB_NAME512})

