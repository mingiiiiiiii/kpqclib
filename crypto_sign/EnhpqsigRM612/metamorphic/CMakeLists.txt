set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    bit_verify.c
    # add extra .c files   
)

set(ENHPQSIG_META_LIB_NAME612 ${PROJECT_NAME}612-meta)
add_library(${ENHPQSIG_META_LIB_NAME612} SHARED ${metamorphic_srcs})

target_include_directories(${ENHPQSIG_META_LIB_NAME612} PUBLIC ../include)
target_compile_definitions(${ENHPQSIG_META_LIB_NAME612} PUBLIC pqsigRM_MODE=1)

add_executable(${ENHPQSIG_META_LIB_NAME612}-main meta_test.c)
target_link_libraries(${ENHPQSIG_META_LIB_NAME612}-main ${ENHPQSIG_META_LIB_NAME612} ${LIB_NAME1})