set(BENCH_NAME2 ${PROJECT_NAME}-II-benchmark)
add_executable(${BENCH_NAME2} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME2} ${LIB_NAME2})

