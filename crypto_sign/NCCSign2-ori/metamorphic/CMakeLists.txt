set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(NCC_META_LIB_NAME2 ${PROJECT_NAME}2-meta)
add_library(${NCC_META_LIB_NAME2} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME2} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME2} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME2} PUBLIC NIMS_MODE=2)

add_executable(${NCC_META_LIB_NAME2}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME2}-main ${NCC_META_LIB_NAME2} ${LIB_NAME2} nccsign2_aes256ctr nccsign2_fips202)


set(NCC_META_LIB_NAME2AES ${PROJECT_NAME}2aes-meta)
add_library(${NCC_META_LIB_NAME2AES} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME2AES} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME2AES} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME2AES} PUBLIC NIMS_MODE=2 NIMS_USE_AES)

add_executable(${NCC_META_LIB_NAME2AES}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME2AES}-main ${NCC_META_LIB_NAME2AES} ${LIB_NAME2aes} nccsign2_aes256ctr nccsign2_fips202)

