

add_executable(${LIB_NAME512}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
#add_executable(${LIB_NAME512}-main main.c ${PROJECT_SOURCE_DIR}/src/rng.c)
target_link_libraries(${LIB_NAME512}-main ${LIB_NAME512} m) 


# add_executable(${LIB_NAME3aes}-main main.c ${PROJECT_SOURCE_DIR}/src/randombytes.c)
# target_link_libraries(${LIB_NAME3aes}-main ${LIB_NAME3aes} nccsign3_aes256ctr nccsign3_fips202) 
