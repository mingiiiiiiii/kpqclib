set(BENCH_NAME576 ${PROJECT_NAME}576-benchmark)
add_executable(${BENCH_NAME576} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME576} ${LIB_NAME576})
target_include_directories(${BENCH_NAME576} PUBLIC ${PROJECT_SOURCE_DIR}/include)

