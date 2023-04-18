
## Select Formats
You can select what images formats you want to support by modifying your ```project.inc``` file.
Add ```DEFINES``` for NO_... to exclude formats that you don't want.

```

#-- JPEG -------------------------------------------------------------------------------------------
# DEFINES += NO_JPEG

#Set this to make auto complete work in QtCreator.
SYSTEM_INCLUDEPATHS_QT_CREATOR += /home/tom/projects/external/emsdk/upstream/emscripten/system/include/
SYSTEM_INCLUDEPATHS_QT_CREATOR += /home/tom/projects/external/emsdk/upstream/emscripten/cache/ports-builds/libjpeg/

SYSTEM_INCLUDEPATHS += /home/tom/projects/external/libjpeg-turbo/install/include
LIBRARYPATHS  += /home/tom/projects/external/libjpeg-turbo/install/lib

# Use either this for libjpeg
# CXXFLAGS += -s USE_LIBJPEG=1
# LDFLAGS += -s USE_LIBJPEG=1

# Or use this if you built libjpeg or libjpeg-turbo locally
LIBS += -ljpeg


#-- WebP -------------------------------------------------------------------------------------------
# DEFINES += NO_WEBP


#-- AVIF -------------------------------------------------------------------------------------------
# DEFINES += NO_AVIF

SYSTEM_INCLUDEPATHS  += /home/tom/projects/external/avif/libavif/include/
LIBRARYPATHS  += /home/tom/projects/external/avif/build/
LIBRARYPATHS  += /home/tom/projects/external/avif/libavif/ext/aom/build.libavif/
LIBRARYPATHS  += /home/tom/projects/external/avif/install/lib/

LIBS += -lavif
LIBS += -ldav1d
# LIBS += -laom


#-- PNG --------------------------------------------------------------------------------------------
# DEFINES += NO_PNG

CXXFLAGS += -s USE_LIBPNG=1
LDFLAGS += -s USE_LIBPNG=1

```


## Build Depedencies

### libjpeg-turbo
Run the follow script to clone and build libjpeg-turbo.
```
tp_image_utils_emcc/build/libjpeg-turbo/build.sh

```

And add it to your ```project.inc``` file:
```
SYSTEM_INCLUDEPATHS += /home/tom/projects/external/libjpeg-turbo/install/include
LIBRARYPATHS  += /home/tom/projects/external/libjpeg-turbo/install/lib
LIBS += -ljpeg

```
