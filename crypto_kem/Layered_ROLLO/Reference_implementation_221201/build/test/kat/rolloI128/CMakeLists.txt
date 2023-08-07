add_library(rbc STATIC IMPORTED)
set_target_properties(rbc PROPERTIES IMPORTED_LOCATION ${RBC_LIB_SOURCE})

add_executable(kat_rolloI_128 main.c)
target_link_libraries(kat_rolloI_128 PUBLIC rbc)

find_package(OpenSSL REQUIRED)
target_link_libraries(kat_rolloI_128 PUBLIC OpenSSL::Crypto)

target_include_directories(kat_rolloI_128 PUBLIC ${RBC_LIB_INCLUDE})

