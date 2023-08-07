set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(PALOMA_META_LIB_NAME5 ${PROJECT_NAME}5-meta)
add_library(${PALOMA_META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${PALOMA_META_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${PALOMA_META_LIB_NAME5} PUBLIC PALOMA_MODE=5)

add_executable(${PALOMA_META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${PALOMA_META_LIB_NAME5}-main ${PALOMA_META_LIB_NAME5} ${LIB_NAME5})