set(metamorphic_srcs
    katrng.c
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(SOLMAE_META_LIB_NAME5 ${PROJECT_NAME}-meta)
add_library(${SOLMAE_META_LIB_NAME5} SHARED ${metamorphic_srcs})

target_include_directories(${SOLMAE_META_LIB_NAME5} PUBLIC ../include)
target_compile_definitions(${SOLMAE_META_LIB_NAME5} PUBLIC SOLMAE_MODE=5)

add_executable(${SOLMAE_META_LIB_NAME5}-main meta_test.c)
target_link_libraries(${SOLMAE_META_LIB_NAME5}-main ${SOLMAE_META_LIB_NAME5} ${LIB_NAME1024})
target_link_libraries(${SOLMAE_META_LIB_NAME5}-main ${LIB_NAME1024} m) 

