set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(TIGER_META_LIB_NAME128 ${PROJECT_NAME}128-meta)
add_library(${TIGER_META_LIB_NAME128} SHARED ${metamorphic_srcs})

target_include_directories(${TIGER_META_LIB_NAME128} PUBLIC ../include)
target_compile_definitions(${TIGER_META_LIB_NAME128} PUBLIC TIGER_MODE=1)

add_executable(${TIGER_META_LIB_NAME128}-main meta_test.c)
target_link_libraries(${TIGER_META_LIB_NAME128}-main ${TIGER_META_LIB_NAME128} ${LIB_NAME1})