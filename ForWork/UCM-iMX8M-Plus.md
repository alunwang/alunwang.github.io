
[How to inspect OpenEmbedded kickstart wic files](https://imxdev.gitlab.io/tutorial/How_to_inspect_OpenEmbedded_kickstart_wic_files/)

```
$ gunzip core-image-base.wic.gz
$ sudo dd if=core-image-base-wic of=/dev/sdX
```

# How to mount .img file
The problem is that the .img files are not images of a partition, but of a whole disk. That means they start with a bootloader and a partition table. You have to find out the offset of the partition and mount it with the offset option of mount.
If you do a
Code:
```
fdisk -l /path/to/image
```
it will show you the block-size and the start-block of the partition. You can use that to calculate the offset.
For example, I have an image of a bootable stick with a 4GB FAT32 partition. The output of the fdisk command is
Code:
Disk Stick.img: 3984 MB, 3984588800 bytes
249 heads, 6 sectors/track, 5209 cylinders, total 7782400 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x0004bfaa

    Device Boot      Start         End      Blocks   Id  System
Stick.img1   *         128     8015999     4007936    b  W95 FAT32
So I have a block-size of 512 bytes and the start-block is 128. The offset is 512 * 128 = 65536.
So the mount command would be
Code:
```
mount -o loop,offset=65536 Stick.img /mnt/tmp
```

# Program to SD
```
$ bunzip2 -dk -f <image_name>.wic.bz2
$ sudo dd if=<image name>.wic of=/dev/sd<partition> bs=1M conv=fsync 
```

