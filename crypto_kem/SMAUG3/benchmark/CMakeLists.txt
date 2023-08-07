set(BENCH_NAME3 ${PROJECT_NAME}3-benchmark)
add_executable(${BENCH_NAME3} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME3} ${LIB_NAME3})
target_include_directories(${BENCH_NAME3} PUBLIC ${PROJECT_SOURCE_DIR}/include)

