set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(NTRUPLUS_META_LIB_NAME576 ${PROJECT_NAME}576-meta)
add_library(${NTRUPLUS_META_LIB_NAME576} SHARED ${metamorphic_srcs})

target_include_directories(${NTRUPLUS_META_LIB_NAME576} PUBLIC ../include)
target_compile_definitions(${NTRUPLUS_META_LIB_NAME576} PUBLIC NTRU_MODE=576)

add_executable(${NTRUPLUS_META_LIB_NAME576}-main meta_test.c)
target_link_libraries(${NTRUPLUS_META_LIB_NAME576}-main ${NTRUPLUS_META_LIB_NAME576} ${LIB_NAME576})