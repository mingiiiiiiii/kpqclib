set(BENCH_NAME3 ${PROJECT_NAME}192-benchmark)
add_executable(${BENCH_NAME3} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME3} ${LIB_NAME3})




