set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(NTRUPLUS_META_LIB_NAME864 ${PROJECT_NAME}864-meta)
add_library(${NTRUPLUS_META_LIB_NAME864} SHARED ${metamorphic_srcs})

target_include_directories(${NTRUPLUS_META_LIB_NAME864} PUBLIC ../include)
target_compile_definitions(${NTRUPLUS_META_LIB_NAME864} PUBLIC NTRU_MODE=864)

add_executable(${NTRUPLUS_META_LIB_NAME864}-main meta_test.c)
target_link_libraries(${NTRUPLUS_META_LIB_NAME864}-main ${NTRUPLUS_META_LIB_NAME864} ${LIB_NAME864})