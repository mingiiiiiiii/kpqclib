set(BENCH_NAME2 ${PROJECT_NAME}2-benchmark)
add_executable(${BENCH_NAME2} speed.c cpucycles.c speed_print.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${BENCH_NAME2} ${LIB_NAME2} nccsign2_fips202 common)

set(BENCH_NAME2aes ${PROJECT_NAME}2aes-benchmark)
add_executable(${BENCH_NAME2aes} speed.c cpucycles.c speed_print.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${BENCH_NAME2aes} ${LIB_NAME2aes} nccsign2_fips202 nccsign2_aes256ctr common)

