# Get the following two copy from Yocto build
tmp/work/armv8a-poky-linux/imx-vpu-hantro-vc/1.8.0-r0/sysroot-destdir/usr/include/hantro_VC8000E_enc # header files, put in /usr/include
tmp/work/armv8a-mx8mp-poky-linux/imx-vpu-hantro/1.26.0-r0/recipe-sysroot # sysroot, can be put anywhere and then provide it in --sysroot-path

# Configure
```
./waf configure --prefix=/home/root/libimxvpuapi/_install --imx-platform=imx8mp --sysroot-path=/home/root/sysroot
```

# Add the following defintion in imxvpuapi2/imxvpuapi2_imx8m_hantro_vc8000_encoder.c
```
#define IMX_DMA_BUFFER_MAPPING_FLAG_MANUAL_SYNC (1UL << 2)
```
Otherwise, there will be "IMX_DMA_BUFFER_MAPPING_FLAG_MANUAL_SYNC" undefined error

# Build
```
./waf
```

# Install