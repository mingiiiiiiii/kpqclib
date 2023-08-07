set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(GCK_META_LIB_NAME3 ${PROJECT_NAME}3-meta)
add_library(${GCK_META_LIB_NAME3} SHARED ${metamorphic_srcs})

target_include_directories(${GCK_META_LIB_NAME3} PUBLIC ../include)
target_compile_definitions(${GCK_META_LIB_NAME3} PUBLIC GCKSign_MODE=3)

add_executable(${GCK_META_LIB_NAME3}-main meta_test.c)
target_link_libraries(${GCK_META_LIB_NAME3}-main ${GCK_META_LIB_NAME3} ${LIB_NAME3})