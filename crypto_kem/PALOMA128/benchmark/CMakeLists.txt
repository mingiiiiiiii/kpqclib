set(BENCH_NAME1 ${PROJECT_NAME}128-benchmark)
add_executable(${BENCH_NAME1} benchmark.c)
target_link_libraries(${BENCH_NAME1} ${LIB_NAME1})