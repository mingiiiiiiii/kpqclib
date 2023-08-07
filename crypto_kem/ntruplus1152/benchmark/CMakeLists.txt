set(BENCH_NAME1152 ${PROJECT_NAME}1152-benchmark)
add_executable(${BENCH_NAME1152} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME1152} ${LIB_NAME1152})
target_include_directories(${BENCH_NAME1152} PUBLIC ${PROJECT_SOURCE_DIR}/include)

