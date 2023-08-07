set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(NCC_META_LIB_NAME5 ${PROJECT_NAME}5-meta)
add_library(${NCC_META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME5} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME5} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME5} PUBLIC NIMS_MODE=5)

add_executable(${NCC_META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME5}-main ${NCC_META_LIB_NAME5} ${LIB_NAME5} nccsign5_aes256ctr nccsign5_fips202)


set(NCC_META_LIB_NAME5AES ${PROJECT_NAME}5aes-meta)
add_library(${NCC_META_LIB_NAME5AES} SHARED ${metamorphic_srcs})

target_include_directories(${NCC_META_LIB_NAME5AES} PUBLIC ../include)
target_include_directories(${NCC_META_LIB_NAME5AES} PUBLIC ../fips)
target_compile_definitions(${NCC_META_LIB_NAME5AES} PUBLIC NIMS_MODE=5 NIMS_USE_AES)

add_executable(${NCC_META_LIB_NAME5AES}-main meta_test.c)
target_link_libraries(${NCC_META_LIB_NAME5AES}-main ${NCC_META_LIB_NAME5AES} ${LIB_NAME5aes} nccsign5_aes256ctr nccsign5_fips202)

