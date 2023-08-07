add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(biix_128 main.c)
target_link_libraries(biix_128 PUBLIC rbc)

target_include_directories(biix_128 PUBLIC ${RBC_LIB_INCLUDE})
