set(BENCH_NAME2 ${PROJECT_NAME}2-benchmark)
add_executable(${BENCH_NAME2} speed.c cpucycles.c speed_print.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${BENCH_NAME2} ${LIB_NAME2})

