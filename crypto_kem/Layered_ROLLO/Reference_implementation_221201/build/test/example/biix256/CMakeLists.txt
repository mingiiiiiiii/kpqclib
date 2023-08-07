add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(biix_256 main.c)
target_link_libraries(biix_256 PUBLIC rbc)

target_include_directories(biix_256 PUBLIC ${RBC_LIB_INCLUDE})
