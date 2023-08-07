

add_executable(${LIB_NAME2}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME2}-main ${LIB_NAME2} nccsign2_fips202) 

add_executable(${LIB_NAME2aes}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME2aes}-main ${LIB_NAME2aes} nccsign2_aes256ctr nccsign2_fips202) 
