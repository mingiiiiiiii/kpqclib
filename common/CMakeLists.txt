cmake_minimum_required(VERSION 3.15)
project(common)

add_library(common 
    aes.c
    fips202.c
    sha2.c
    #kisa_sha2.c
)

