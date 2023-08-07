

add_executable(${LIB_NAME5}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME5}-main ${LIB_NAME5} nccsign5_fips202) 

add_executable(${LIB_NAME5aes}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
target_link_libraries(${LIB_NAME5aes}-main ${LIB_NAME5aes} nccsign5_aes256ctr nccsign5_fips202) 
