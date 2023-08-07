set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(ENHPQSIG_META_LIB_NAME613 ${PROJECT_NAME}613-meta)
add_library(${ENHPQSIG_META_LIB_NAME613} SHARED ${metamorphic_srcs})

target_include_directories(${ENHPQSIG_META_LIB_NAME613} PUBLIC ../include)
target_compile_definitions(${ENHPQSIG_META_LIB_NAME613} PUBLIC pqsigRM_MODE=5)

add_executable(${ENHPQSIG_META_LIB_NAME613}-main meta_test.c)
target_link_libraries(${ENHPQSIG_META_LIB_NAME613}-main ${ENHPQSIG_META_LIB_NAME613} ${LIB_NAME5})