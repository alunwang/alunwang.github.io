[gstreamer-toolkit](https://github.com/dabrain34/gstreamer-toolkit)
[Cross-compiling with gst-build and GStreamer](https://www.collabora.com/news-and-blog/blog/2020/05/15/cross-compiling-with-gst-build-and-gstreamer/)


# The content used in the cross file aarch64-linux-meson-cross-file.txt
```
[host_machine]
system = 'linux'
cpu_family = 'aarch64'
cpu = 'arm64'
endian = 'little'

[properties]
pkg_config_libdir = ['__no_cross_sysroot__']
sys_root = ''


[binaries]
c = ['/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc']
cpp = ['/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++']
ar = ['/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-ar']
pkgconfig = 'pkg-config'
strip = ['/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-strip']
cmake = ['false']
```


# Configure
```
meson build --cross-file=./aarch64-linux-meson-cross-file.txt --prefix=/usr -D sharp=disabled  -D libav=disabled -D rtsp_server=enabled -D vaapi=disabled -Dugly=disabled -Dgtk_doc=disabled -Dglib:libmount=disabled -Dintrospection=disabled
```

# Build
```
ninja -C build
```

# Install
```
ninja -c build install
```
This will install the files to /usr (specified in --prefix during configure)
or: 
```
DESTDIR=/home/alan/V4L2/gstreamer-1.20.3/_install ninja -C build install
```