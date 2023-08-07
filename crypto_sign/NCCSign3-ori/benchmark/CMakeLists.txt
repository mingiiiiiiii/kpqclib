set(BENCH_NAME3 ${PROJECT_NAME}3-benchmark)
add_executable(${BENCH_NAME3} speed.c cpucycles.c speed_print.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${BENCH_NAME3} ${LIB_NAME3} nccsign3_fips202 common)

set(BENCH_NAME3aes ${PROJECT_NAME}3aes-benchmark)
add_executable(${BENCH_NAME3aes} speed.c cpucycles.c speed_print.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${BENCH_NAME3aes} ${LIB_NAME3aes} nccsign3_fips202 nccsign3_aes256ctr common)
