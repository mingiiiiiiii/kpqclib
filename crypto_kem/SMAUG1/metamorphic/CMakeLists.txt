set(metamorphic_srcs
    bit_contribution.c    
    bit_exclusion.c 
    # add extra .c files   
)

set(META_LIB_NAME1 ${PROJECT_NAME}1-meta)
add_library(${META_LIB_NAME1} SHARED ${metamorphic_srcs})

target_include_directories(${META_LIB_NAME1} PUBLIC ../include)
target_compile_definitions(${META_LIB_NAME1} PUBLIC CRYPTO_ALGNAME="SMAUG1_KEM")
target_compile_definitions(${META_LIB_NAME1} PUBLIC SMAUG_MODE=1)

add_executable(${META_LIB_NAME1}-main meta_test.c)
target_link_libraries(${META_LIB_NAME1}-main ${META_LIB_NAME1} ${LIB_NAME1})