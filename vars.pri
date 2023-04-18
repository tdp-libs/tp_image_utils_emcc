TARGET = tp_image_utils_emcc
TEMPLATE = lib

DEFINES += TP_IMAGE_UTILS_EMCC_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_image_utils_emcc/Globals.h


SOURCES += src/LoadImages.cpp
HEADERS += inc/tp_image_utils_emcc/LoadImages.h

SOURCES += src/ReadJPEG.cpp
HEADERS += inc/tp_image_utils_emcc/ReadJPEG.h

SOURCES += src/ReadPNG.cpp
HEADERS += inc/tp_image_utils_emcc/ReadPNG.h

SOURCES += src/ReadWebP.cpp
HEADERS += inc/tp_image_utils_emcc/ReadWebP.h
