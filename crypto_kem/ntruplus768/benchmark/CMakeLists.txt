set(BENCH_NAME768 ${PROJECT_NAME}768-benchmark)
add_executable(${BENCH_NAME768} speed.c cpucycles.c speed_print.c)
target_link_libraries(${BENCH_NAME768} ${LIB_NAME768})
target_include_directories(${BENCH_NAME768} PUBLIC ${PROJECT_SOURCE_DIR}/include)

