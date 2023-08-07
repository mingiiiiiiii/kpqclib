set(BENCH_NAME864 ${PROJECT_NAME}864-benchmark)
add_executable(${BENCH_NAME864} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME864} ${LIB_NAME864})
target_include_directories(${BENCH_NAME864} PUBLIC ${PROJECT_SOURCE_DIR}/include)

