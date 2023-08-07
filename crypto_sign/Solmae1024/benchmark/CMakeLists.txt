set(BENCH_NAME1024 ${PROJECT_NAME}-benchmark)
add_executable(${BENCH_NAME1024} speed.c cpucycles.c speed_print.c)
# target_link_libraries(${BENCH_NAME1} ${LIB_NAME512} common)


target_link_libraries(${BENCH_NAME1024} ${LIB_NAME1024} m) 


