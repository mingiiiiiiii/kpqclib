set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(AIMER_META_LIB_NAME1 ${PROJECT_NAME}1-meta)
add_library(${AIMER_META_LIB_NAME1} SHARED ${metamorphic_srcs})

target_include_directories(${AIMER_META_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${AIMER_META_LIB_NAME1} PUBLIC AIMER_MODE=1)

add_executable(${AIMER_META_LIB_NAME1}-main meta_test.c)
target_link_libraries(${AIMER_META_LIB_NAME1}-main ${AIMER_META_LIB_NAME1} ${LIB_NAME1})