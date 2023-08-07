set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(TIGER_META_LIB_NAME256 ${PROJECT_NAME}256-meta)
add_library(${TIGER_META_LIB_NAME256} SHARED ${metamorphic_srcs})

target_include_directories(${TIGER_META_LIB_NAME256} PUBLIC ../include)
target_compile_definitions(${TIGER_META_LIB_NAME256} PUBLIC TIGER_MODE=5)

add_executable(${TIGER_META_LIB_NAME256}-main meta_test.c)
target_link_libraries(${TIGER_META_LIB_NAME256}-main ${TIGER_META_LIB_NAME256} ${LIB_NAME5})