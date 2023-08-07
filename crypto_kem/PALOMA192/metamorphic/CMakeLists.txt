set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(PALOMA_META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${PALOMA_META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${PALOMA_META_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${PALOMA_META_LIB_NAME3} PUBLIC PALOMA_MODE=3)

add_executable(${PALOMA_META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${PALOMA_META_LIB_NAME3}-main ${PALOMA_META_LIB_NAME3} ${LIB_NAME3})