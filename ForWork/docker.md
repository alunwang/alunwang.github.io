
# 创建镜像
sudo docker build -t yocto-build:v1 - < $(pwd)/work/Dockerfile-20.04 # 使用Dockerfile-20.4文件来创建镜像，-t指定镜像的名字和标签为yocto-build:v1

## 使用镜像yocto-build:v1创建一个容器，以交互方式运行
sudo docker run --interactive --tty --privileged --volume $(pwd)/work:/work yocto-build:v1

相当于进入容器并开启一个新的终端，使用exit退出，容器也不会停止。
```
sudo docker exec -it 容器id /bin/bash
```

#
``` 
sudo docker ps
sudo docker rm container_id, ...
sudo docker rmi image_file
```


# Copy file out
First check the docker container running
```
sudo docker ps
```
Get its ID and then copy file out
```
sudo docker cp 4a683b7dce1f:/work/in-work/compulab-nxp-bsp/build/hantro.tar.gz ./
```
Copy the file /work/in-work/compulab-nxp-bsp/build/hantro.tar.gz in 4a683b7dce1f docker container to local host at ./