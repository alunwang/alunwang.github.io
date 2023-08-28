# Issue and notes when using pkg-config for including the header files and linking the libraries for a package:


```
# Gstreamer
set(gstreamer_DIR /home/alan/V4L2/gstreamer-1.20.3/_install/usr)
set(ENV{PKG_CONFIG_PATH} "${gstreamer_DIR}/lib/pkgconfig")  ## PKG_CONFIG_PATH设置在什么目录查找一个包的.pc，一般是/usr/lib/pkgconfig

pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET    ## 数据包名，就是通过上面目录下gstreamer-1.0.pc文件确定
    gstreamer-1.0
)

message(STATUS "=== GSTREAMER_LIBRARIES: ${GSTREAMER_LIBRARIES}")   ## 特别注意gstreamer-1.0.pc文件里面的"prefix"属性，缺省一般是"/usr"
message(STATUS "=== GSTREAMER_INCLUDE_DIRS: ${GSTREAMER_INCLUDE_DIRS}")
message(STATUS "=== GSTREAMER_LIBRARY_DIRS: ${GSTREAMER_LIBRARY_DIRS}") 
message(STATUS "=== GSTREAMER_CFLAGS: ${GSTREAMER_CFLAGS}") 


target_link_libraries(${PROJECT_NAME} PkgConfig::GSTREAMER) ## 链接库进目标
```

# .../aarch64-none-linux-gnu/bin/ld: warning: libgmodule-2.0.so.0, needed by /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgstreamer-1.0.so, not found (try using -rpath or -rpath-link)

- Check if /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgmodule-2.0.so.0 exists?
```
alan@AAS83:~/v4l2Capture/build$ ls /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgmodule-2.0.so.0* -l
lrwxrwxrwx 1 alan alan    26 Jun 19 11:22 /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgmodule-2.0.so.0 -> libgmodule-2.0.so.0.7400.1
-rwxr-xr-x 1 alan alan 55280 Jun 19 11:22 /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgmodule-2.0.so.0.7400.1
```
- Check if /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/pkgconfig/gmodule-2.0.pc exists?
```
ls -l /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/pkgconfig/gmodule-2.0.pc 
-rw-r--r-- 1 alan alan 295 Jun 29 08:53 /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/pkgconfig/gmodule-2.0.pc
```
- Add 'gmodule-2.0' to pkg_check_modules() in CMakeLists.txt as this:
```
pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET
    gstreamer-1.0
    gmodule-2.0
    ffi
    pcre2-8
)
```

# undefined reference to `stat64@GLIBC_2.33'
/home/alan/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/../lib/gcc/aarch64-none-linux-gnu/10.2.1/../../../../aarch64-none-linux-gnu/bin/ld: /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libgstreamer-1.0.so: undefined reference to `stat64@GLIBC_2.33'
/home/alan/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/../lib/gcc/aarch64-none-linux-gnu/10.2.1/../../../../aarch64-none-linux-gnu/bin/ld: /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libglib-2.0.so: undefined reference to `fstat64@GLIBC_2.33'
/home/alan/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/../lib/gcc/aarch64-none-linux-gnu/10.2.1/../../../../aarch64-none-linux-gnu/bin/ld: /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libglib-2.0.so: undefined reference to `pthread_sigmask@GLIBC_2.32'
/home/alan/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/../lib/gcc/aarch64-none-linux-gnu/10.2.1/../../../../aarch64-none-linux-gnu/bin/ld: /home/alan/V4L2/gstreamer-1.22.3/_install/usr/lib/libglib-2.0.so: undefined reference to `lstat64@GLIBC_2.33'

这些错误是由于使用不同版本编译器（也就是其中的glibc库不同）编译库和应用导致。