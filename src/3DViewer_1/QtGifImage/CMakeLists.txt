cmake_minimum_required(VERSION 3.5)

project(GIFQT VERSION 0.1 LANGUAGES CXX C)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(GIFQT
    giflib/dgif_lib.c
    giflib/egif_lib.c
    giflib/gif_err.c
    giflib/gif_font.c
    giflib/gif_hash.c
    giflib/gif_hash.h
    giflib/gif_lib_private.h
    giflib/gif_lib.h
    giflib/gifalloc.c
    giflib/quantize.c
    gifimage/qgifglobal.h
    gifimage/qgifimage_p.h
    gifimage/qgifimage.cpp
    gifimage/qgifimage.h
)

target_link_libraries(GIFQT Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)