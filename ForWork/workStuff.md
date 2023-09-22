# This is to record some stuff during working.

[Docker usage](docker.md)

### How to enable the ping from outside in Windows 11
By default, the firewall in Windows disable the ping in, a quick way to enable the ping in from outside in Windows 11 is provided in [How to Allow Ping in Windows Firewall.](https://www.wintips.org/how-to-allow-ping-in-windows-firewall/) 


### Install the cross compiler
```
$ sudo apt-get install gcc-aarch64-linux-gnu
Export the environment variables:
$ export ARCH=arm64
$ export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-
```