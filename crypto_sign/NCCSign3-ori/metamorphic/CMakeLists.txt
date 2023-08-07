set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(NCC_META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${NCC_META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME3} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME3} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME3} PUBLIC NIMS_MODE=3)

add_executable(${NCC_META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME3}-main ${NCC_META_LIB_NAME3} ${LIB_NAME3} nccsign3_aes256ctr nccsign3_fips202)


set(NCC_META_LIB_NAME3AES ${PROJECT_NAME}3aes-meta)
add_library(${NCC_META_LIB_NAME3AES} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME3AES} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME3AES} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME3AES} PUBLIC NIMS_MODE=3 NIMS_USE_AES)

add_executable(${NCC_META_LIB_NAME3AES}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME3AES}-main ${NCC_META_LIB_NAME3AES} ${LIB_NAME3aes} nccsign3_aes256ctr nccsign3_fips202)

