live555 depends on openssl, so we need to get and cross compile openssl first

# Cross compille openssl
```
wget https://www.openssl.org/source/old/1.1.1/openssl-1.1.1s.tar.gz
tar zxvf openssl-1.1.1s.tar.gz
cd openssl-1.1.1s

./config no-asm shared no-async --prefix=/home/alan/V4L2/openssl-1.1.1s/_install --cross-compile-prefix=/home/alan/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
sed -i 's/-m64//' Makefile
make && make install
```

# Cross compile live555
```
wget http://www.live555.com/liveMedia/public/live555-latest.tar.gz
tar zxvf live555-latest.tar.gz
mv live live555
cd live555

cp config.armlinux config.aarch64linux
chmod 644 config.aarch64linux
```
Change the content of config.aarch64linux as below:
```
CROSS_COMPILE?=         /home/alan/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu- # cross compiler prefix
COMPILE_OPTS =          $(INCLUDES) -I/home/alan/V4L2/openssl-1.1.1s/_install/include -I. -O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 # include file of openssl
C =                     c
C_COMPILER =            $(CROSS_COMPILE)gcc
C_FLAGS =               $(COMPILE_OPTS)
CPP =                   cpp
CPLUSPLUS_COMPILER =    $(CROSS_COMPILE)g++
CPLUSPLUS_FLAGS =       $(COMPILE_OPTS) -Wall -DBSD=1
OBJ =                   o
LINK =                  $(CROSS_COMPILE)g++ -o
LDFLAGS =               -L/home/alan/V4L2/openssl-1.1.1s/_install/lib # library of openssl
LINK_OPTS =             $(LDFLAGS) # include LDFLAGS
CONSOLE_LINK_OPTS =     $(LINK_OPTS)
LIBRARY_LINK =          $(CROSS_COMPILE)ar cr 
LIBRARY_LINK_OPTS =     $(LINK_OPTS)
LIB_SUFFIX =                    a
LIBS_FOR_CONSOLE_APPLICATION = -lssl -lcrypto
LIBS_FOR_GUI_APPLICATION =
EXE =
```
Then it can be cross compiled as below
```
./genMakefiles aarch64linux
make
```
And it can be copied to the board:
```
scp live555Mediaserver root@172.16.0.2:~/
```
if there is no openssl installed on the board, we need to copy it to the board also.
