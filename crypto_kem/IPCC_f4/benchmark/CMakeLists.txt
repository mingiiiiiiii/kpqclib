set(BENCH_NAME4 ${PROJECT_NAME}4-benchmark)
add_executable(${BENCH_NAME4} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME4} ${LIB_NAME4})




