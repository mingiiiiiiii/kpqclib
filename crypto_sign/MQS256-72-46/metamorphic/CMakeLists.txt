set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(MQS256_META_LIB_NAME2 ${PROJECT_NAME}-72-46-meta)
add_library(${MQS256_META_LIB_NAME2} SHARED ${metamorphic_srcs})

target_include_directories(${MQS256_META_LIB_NAME2} PUBLIC ../include)
target_compile_definitions(${MQS256_META_LIB_NAME2} PUBLIC MQS256_MODE=2)

add_executable(${MQS256_META_LIB_NAME2}-main meta_test.c)
target_link_libraries(${MQS256_META_LIB_NAME2}-main ${MQS256_META_LIB_NAME2} ${LIB_NAME2})