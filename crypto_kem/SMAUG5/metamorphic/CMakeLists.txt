set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(META_LIB_NAME5 ${PROJECT_NAME}5-meta)
add_library(${META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${META_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${META_LIB_NAME5} PUBLIC CRYPTO_ALGNAME="SMAUG5_KEM")
target_compile_definitions(${META_LIB_NAME5} PUBLIC SMAUG_MODE=5)

add_executable(${META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${META_LIB_NAME5}-main ${META_LIB_NAME5} ${LIB_NAME5})