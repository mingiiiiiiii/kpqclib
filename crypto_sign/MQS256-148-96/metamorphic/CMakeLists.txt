set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(MQS256_META_LIB_NAME5 ${PROJECT_NAME}-148-96-meta)
add_library(${MQS256_META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${MQS256_META_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${MQS256_META_LIB_NAME5} PUBLIC MQS256_MODE=5)

add_executable(${MQS256_META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${MQS256_META_LIB_NAME5}-main ${MQS256_META_LIB_NAME5} ${LIB_NAME5})