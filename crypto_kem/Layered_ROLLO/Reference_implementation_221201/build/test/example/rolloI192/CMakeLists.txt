add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(rolloI_192 main.c)
target_link_libraries(rolloI_192 PUBLIC rbc)

target_include_directories(rolloI_192 PUBLIC ${RBC_LIB_INCLUDE})
