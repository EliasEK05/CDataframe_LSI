cmake_minimum_required(VERSION 3.27)
project(projetCDataframe_main C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(projetCDataframe_main
        tri.c
        dataframe_ops.c
        colonne_ops.c
        cdt_creation.c
        main.c
        projet.h)
