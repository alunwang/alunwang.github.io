# Set up x264
```
./configure --prefix=/home/alan/V4L2/x264-master/_install --enable-shared --enable-static --host=arm-linux --cross-prefix=/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu- --disable-opencl --enable-pic --disable-asm
make
make install
```

# Set up FFMGEG
```
./configure --pkg-config='pkg-config --static' --enable-cross-compile --cross-prefix=/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu- --arch=arm64 --target-os=linux --prefix=/home/alan/V4L2/ffmpeg-6.0/_install --enable-gpl --enable-libx264 --extra-cflags=-I/home/alan/V4L2/x264-master/_install/include --extra-ldflags=-L/home/alan/V4L2/x264-master/_install/lib --extra-libs=-ldl
make
make install
```

# Include the headers and lib to a project in CMakeLists.txt
```
set(ffmpeg_DIR /home/alan/V4L2/ffmpeg-6.0/_install)
set(ENV{PKG_CONFIG_PATH} "${ffmpeg_DIR}/lib/pkgconfig") #Path to search for the pkgconfig files for each lib
find_package(PkgConfig REQUIRED)    #Make sure the PkgConfig is installed
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
    libpostproc
)
# message(STATUS "=== FFMPEG_LIBRARIES: ${FFMPEG_LIBRARIES}")
# message(STATUS "=== FFMPEG_INCLUDE_DIRS: ${FFMPEG_INCLUDE_DIRS}")
# message(STATUS "=== FFMPEG_LIBRARY_DIRS: ${FFMPEG_LIBRARY_DIRS}") 
# message(STATUS "=== FFMPEG_CFLAGS: ${FFMPEG_CFLAGS}") 

set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

target_link_libraries(${PROJECT_NAME} PkgConfig::FFMPEG)
```

# Appendix
Configuration options with ./configure saved in the file configure.log