set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(AIMER_META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${AIMER_META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${AIMER_META_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${AIMER_META_LIB_NAME3} PUBLIC AIMER_MODE=3)

add_executable(${AIMER_META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${AIMER_META_LIB_NAME3}-main ${AIMER_META_LIB_NAME3} ${LIB_NAME3})