set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(TIGER_META_LIB_NAME192 ${PROJECT_NAME}192-meta)
add_library(${TIGER_META_LIB_NAME192} SHARED ${metamorphic_srcs})

target_include_directories(${TIGER_META_LIB_NAME192} PUBLIC ../include)
target_compile_definitions(${TIGER_META_LIB_NAME192} PUBLIC TIGER_MODE=3)

add_executable(${TIGER_META_LIB_NAME192}-main meta_test.c)
target_link_libraries(${TIGER_META_LIB_NAME192}-main ${TIGER_META_LIB_NAME192} ${LIB_NAME3})