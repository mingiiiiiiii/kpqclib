set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(PALOMA_META_LIB_NAME1 ${PROJECT_NAME}1-meta)
add_library(${PALOMA_META_LIB_NAME1} SHARED ${metamorphic_srcs})

target_include_directories(${PALOMA_META_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${PALOMA_META_LIB_NAME1} PUBLIC PALOMA_MODE=1)

add_executable(${PALOMA_META_LIB_NAME1}-main meta_test.c)
target_link_libraries(${PALOMA_META_LIB_NAME1}-main ${PALOMA_META_LIB_NAME1} ${LIB_NAME1})