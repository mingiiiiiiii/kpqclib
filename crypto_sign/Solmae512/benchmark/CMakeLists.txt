set(BENCH_NAME512 ${PROJECT_NAME}-benchmark)
add_executable(${BENCH_NAME512} speed.c cpucycles.c speed_print.c)
# target_link_libraries(${BENCH_NAME1} ${LIB_NAME512} common)


target_link_libraries(${BENCH_NAME512} ${LIB_NAME512} m) 


