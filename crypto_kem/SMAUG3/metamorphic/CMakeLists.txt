set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${META_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${META_LIB_NAME3} PUBLIC CRYPTO_ALGNAME="SMAUG3_KEM")
target_compile_definitions(${META_LIB_NAME3} PUBLIC SMAUG_MODE=3)

add_executable(${META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${META_LIB_NAME3}-main ${META_LIB_NAME3} ${LIB_NAME3})