set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(PEREGRINE_META_LIB_NAME512 ${PROJECT_NAME}512-meta)
add_library(${PEREGRINE_META_LIB_NAME512} SHARED ${metamorphic_srcs})

target_include_directories(${PEREGRINE_META_LIB_NAME512} PUBLIC ../include)
target_compile_definitions(${PEREGRINE_META_LIB_NAME512} PUBLIC Peregrine_MODE=9)

add_executable(${PEREGRINE_META_LIB_NAME512}-main meta_test.c)
target_link_libraries(${PEREGRINE_META_LIB_NAME512}-main ${PEREGRINE_META_LIB_NAME512} ${LIB_NAME512})