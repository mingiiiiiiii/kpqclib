set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(HAETAE_META_LIB_NAME5 ${PROJECT_NAME}5-meta)
add_library(${HAETAE_META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${HAETAE_META_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${HAETAE_META_LIB_NAME5} PUBLIC HAETAE_MODE=5)

add_executable(${HAETAE_META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${HAETAE_META_LIB_NAME5}-main ${HAETAE_META_LIB_NAME5} ${LIB_NAME5})