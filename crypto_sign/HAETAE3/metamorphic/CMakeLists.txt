set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(HAETAE_META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${HAETAE_META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${HAETAE_META_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${HAETAE_META_LIB_NAME3} PUBLIC HAETAE_MODE=3)

add_executable(${HAETAE_META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${HAETAE_META_LIB_NAME3}-main ${HAETAE_META_LIB_NAME3} ${LIB_NAME3})