# Some wsl command
```
wsl --shutdown
wsl --update # update wsl
```


# Check space occupied

```
wsl df -h /mnt/wslg/distro

wsl df -h /                                                                                                                             
```

[How do I get back unused disk space from Ubuntu on WSL2?](https://superuser.com/questions/1606213/how-do-i-get-back-unused-disk-space-from-ubuntu-on-wsl2)

```
wsl --shutdown
Optimize-VHD -Path C:\Users\user\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu20.04onWindows_79rhkp1fndgsc\LocalState\ext4.vhdx -Mode Full
```
