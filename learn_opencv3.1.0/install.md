# 安装软件包

## mac下安装

1. 下载软件包源码 `https://opencv.org/releases/opencv-3.4.13`
2. 解压安装包 `tar -xvf opencv-3.4.13.zip`
3. 进入目录 `cd opencv-3.4.13`
4. 执行cmake标准步骤 `mkdir build; cd build`
5. 执行编译 `cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..`
6. `make -j6`＃并行运行6个作业
7. `sudo make install`

## windwos下安装

## linux下安装

## 参考资料

1. [opencv在mac上安装和配置](https://www.jianshu.com/p/564c8b352c7f)
