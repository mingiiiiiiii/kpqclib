set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(NTRUPLUS_META_LIB_NAME1152 ${PROJECT_NAME}1152-meta)
add_library(${NTRUPLUS_META_LIB_NAME1152} SHARED ${metamorphic_srcs})

target_include_directories(${NTRUPLUS_META_LIB_NAME1152} PUBLIC ../include)
target_compile_definitions(${NTRUPLUS_META_LIB_NAME1152} PUBLIC NTRU_MODE=1152)

add_executable(${NTRUPLUS_META_LIB_NAME1152}-main meta_test.c)
target_link_libraries(${NTRUPLUS_META_LIB_NAME1152}-main ${NTRUPLUS_META_LIB_NAME1152} ${LIB_NAME1152})