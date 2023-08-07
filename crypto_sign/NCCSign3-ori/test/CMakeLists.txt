

add_executable(${LIB_NAME3}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME3}-main ${LIB_NAME3} nccsign3_fips202) 

add_executable(${LIB_NAME3aes}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME3aes}-main ${LIB_NAME3aes} nccsign3_aes256ctr nccsign3_fips202) 
