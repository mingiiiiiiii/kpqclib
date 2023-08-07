set(BENCH_NAME5 ${PROJECT_NAME}-V-benchmark)
add_executable(${BENCH_NAME5} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME5} ${LIB_NAME5})

