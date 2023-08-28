# Instruction to cross compile the OpenCV

wget https://github.com/opencv/opencv/archive/refs/tags/4.7.0.tar.gz

tar zxvf 4.7.0.tar.gz

cd opencv-4.7.0

Change the platforms/linux/aarch64-gnu.toolchain.cmake as below:
```
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(GCC_COMPILER_VERSION "" CACHE STRING "GCC Compiler version")
set(CMAKE_C_COMPILER /home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)
set(GNU_MACHINE "aarch64-none-linux-gnu" CACHE STRING "GNU compiler triple")
include("${CMAKE_CURRENT_LIST_DIR}/arm.toolchain.cmake")
```
```
mkdir -p build _install
cd build

cmake -DCMAKE_INSTALL_PREFIX=../_install -DWITH_GSTREAMER=ON -DHAVE_GSTREAMER=ON -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/aarch64-gnu.toolchain.cmake ..
make -j$(nproc)
make install # this will install in opencv-4.7.0/_install directory
```

# Instruction to include the OpenCV headers and library into a project
Add the following content into the CMakeLists.txt
```
INCLUDE_DIRECTORIES(/home/alan/V4L2/opencv-4.7.0/_install/include/opencv4)

set(OpenCV_DIR /home/alan/V4L2/opencv-4.7.0/build)
find_package(OpenCV 4.7.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})s
```


[Compiling OpenCV from Source](https://developer.ridgerun.com/wiki/index.php/Compiling_OpenCV_from_Source)