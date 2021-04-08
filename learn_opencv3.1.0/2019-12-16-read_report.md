---
layout: post
title: 教程读后感
date: 2019-11-12 15:13:09
description: 教程读后感
tag: OpenCV3.1.0学习

---

- [1. 1.OPENCV3.1的API介绍](#1-1opencv31的api介绍)
  - [1.2.1. pptx概述](#121-pptx概述)
  - [1.2.2. 基本演示](#122-基本演示)
  - [1.2.3. 掩膜操作](#123-掩膜操作)
  - [1.2.4. Mat对象](#124-mat对象)
  - [1.2.5. 图像操作](#125-图像操作)
  - [1.2.6. 图像混合](#126-图像混合)
  - [1.2.7. 亮度与对比度](#127-亮度与对比度)
  - [1.2.8. 绘制形状与文字](#128-绘制形状与文字)
  - [1.2.9. 均值+高斯](#129-均值高斯)
  - [1.2.10. 中值+高斯双边](#1210-中值高斯双边)
  - [1.2.11. 膨胀与腐蚀](#1211-膨胀与腐蚀)
  - [1.2.12. 形态学操作](#1212-形态学操作)
  - [1.2.13. 提取水平与垂直线](#1213-提取水平与垂直线)
  - [1.2.14. 上采样和降采样](#1214-上采样和降采样)
  - [1.2.15. 基本阈yu值操作](#1215-基本阈yu值操作)
  - [1.2.16. 自定义线性滤波](#1216-自定义线性滤波)
  - [1.2.17. 卷积边缘](#1217-卷积边缘)
  - [1.2.18. Sobel算子](#1218-sobel算子)
  - [1.2.19. Laplance算子](#1219-laplance算子)
  - [1.2.20.](#1220)
  - [1.2.21.](#1221)
  - [1.2.22.](#1222)
  - [1.2.23.](#1223)
  - [1.2.24.](#1224)
  - [1.2.25.](#1225)
  - [1.2.26.](#1226)
  - [1.2.27.](#1227)
  - [1.2.28.](#1228)
  - [1.2.29.](#1229)
  - [1.2.30.](#1230)
  - [1.2.31.](#1231)
  - [1.2.32.](#1232)
  - [1.2.33.](#1233)
  - [1.2.34.](#1234)

# 1. 1.OPENCV3.1的API介绍

基于版本OpenCV3.1.0学习

## 1.2.1. pptx概述

- 说明: 概述, 介绍什么是OpenCV, OpenCV是计算机视觉开源库, 主要算法涉及图像处理和机器学习相关方法, 是Intel公司贡献出来的, 俄罗斯工程师贡献大部分C/C++带代码。
- HighGUI部分
- Image Process
- 2D Feature
- Camera Calibration and 3D reconstruction
- Video Analysis
- Object Detection
- Machine Learning
- GPU加速

## 1.2.2. 基本演示

- 说明: 基本演示, 主要使用三个函数
  - 加载图像（用cv::imread）
  - 修改图像 (cv::cvtColor)
  - 保存图像(cv::imwrite)
  - 读取图片, 然后图片值与255取反, 输出。
  - 代码: chapter_001.cpp

## 1.2.3. 掩膜操作

- 说明: 掩膜操作, 指针ptr及`filter2D`进行掩膜操作
- 读取图片, 对图片做掩膜操作, 然后输出。
- 掩膜的本质就是使用`kernel`矩阵, 对原始矩阵进行求和, 结果作为锚的输出。
- void filter2D( InputArray src, OutputArray dst, int ddepth,
                               InputArray kernel, Point anchor = Point(-1,-1),
                               double delta = 0, int borderType = BORDER_DEFAULT );进行掩膜操作
- void Sobel( InputArray src, OutputArray dst, int ddepth,
                            int dx, int dy, int ksize = 3,
                            double scale = 1, double delta = 0,
                            int borderType = BORDER_DEFAULT );//索贝尔方法, 一种常用的边缘检测算子, 是一阶的梯度算法。对噪声具有平滑作用, 提供较为精确的边缘方向信息, 边缘定位精度不够高。当对精度要求不是很高时, 是一种较为常用的边缘检测方法。
    代码: chapter_002.cpp/chapter_003.cpp/chapter_004.cpp

## 1.2.4. Mat对象

- 说明: Mat对象
- void cvtColor( InputArray src, OutputArray dst, int code, int dstCn = 0 );  
- MatExpr eye(int rows, int cols, int type);创建单位矩阵
   代码: chapter_004.cpp

## 1.2.5. 图像操作

- 说明: 图像操作, 修改某一个像素值。
- 图片的颜色空间变换演示
   代码: chapter_005.cpp

## 1.2.6. 图像混合

- 说明: 图像混合
- void addWeighted(InputArray src1, double alpha, InputArray src2,
                              double beta, double gamma, OutputArray dst, int dtype = -1);二张图像混合
   代码: chapter_006.cpp

## 1.2.7. 亮度与对比度

- 说明: 亮度与对比度,通过修改像素值来体现
- MatExpr zeros(Size size, int type);//初始化0值矩阵
   代码: chapter_007.cpp

## 1.2.8. 绘制形状与文字

- 说明: 绘制形状与文字
- 画线 cv::line （LINE_4\LINE_8\LINE_AA）
- 画椭圆cv::ellipse
- 画矩形cv::rectangle
- 画圆cv::circle
- 画填充cv::fillPoly
   代码: chapter_008.cpp/chapter_009.cpp

## 1.2.9. 均值+高斯

- 说明: 均值模糊+高斯模糊
- 模糊原理, 卷积计算, 线性滤波Smooth/Blur(均值模糊blur/高斯模糊GaussianBlur)
- void blur( InputArray src, OutputArray dst,
                        Size ksize, Point anchor = Point(-1,-1),
                        int borderType = BORDER_DEFAULT );//均值模糊
- void GaussianBlur( InputArray src, OutputArray dst, Size ksize,
                                double sigmaX, double sigmaY = 0,
                                int borderType = BORDER_DEFAULT );//高斯模糊
    代码: chapter_010.cpp

## 1.2.10. 中值+高斯双边

- 说明: 中值模糊+高斯双边模糊, 中值对椒盐噪声有很好的抑制作用
- 中值模糊medianBlur+双边模糊bilateralFilter
- void medianBlur( InputArray src, OutputArray dst, int ksize );中值模糊, 中值对椒盐噪声有很好的抑制作用,ksize必须>1且必须是基数
- void bilateralFilter( InputArray src, OutputArray dst, int d,
                                       double sigmaColor, double sigmaSpace,
                                       int borderType = BORDER_DEFAULT );//双边模糊, d:计算半径,sigmaColor:计算的像素差值,sigmaSpace:如果d>0忽略,如果d<0,根据它来计算d
- 均值模糊无法克服边缘像素信息丢失缺陷。原因是均值滤波是基于平均权重
- 高斯模糊部分克服了该缺陷, 但是无法完全避免, 因为没有考虑像素值的不同
- 高斯双边模糊 – 是边缘保留的滤波方法, 避免了边缘信息丢失, 保留了图像轮廓不变
    代码: chapter_011.cpp

## 1.2.11. 膨胀与腐蚀

- 说明: 膨胀与腐蚀, 形态学基本操作
- 膨胀: 跟卷积操作类似, 假设有图像A和结构元素B, 结构元素B在A上面移动, 其中B定义其中心为锚点, 计算B覆盖下A的最大像素值用来替换锚点的像素, 其中B作为结构体可以是任意形状
- 腐蚀: 跟膨胀操作的过程类似, 唯一不同的是以最小值替换锚点重叠下图像的像素值
- Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));//生成kernel,返回值作为dilate和erode的第三个参数, 可以构建各种kernel, shape: MORPH_RECT/MORPH_CROSS/MORPH_ELLIPSE
- void dilate( InputArray src, OutputArray dst, InputArray kernel,
                          Point anchor = Point(-1,-1), int iterations = 1,
                          int borderType = BORDER_CONSTANT,
                          const Scalar& borderValue = morphologyDefaultBorderValue() );膨胀
- void erode( InputArray src, OutputArray dst, InputArray kernel,
                         Point anchor = Point(-1,-1), int iterations = 1,
                         int borderType = BORDER_CONSTANT,
                         const Scalar& borderValue = morphologyDefaultBorderValue() );腐蚀
    代码: chapter_012.cpp

## 1.2.12. 形态学操作

- 说明: 形态学操作, 包括: 开, 闭, 梯度, 顶帽, 黑帽等
- 开操作- open, 先腐蚀后膨胀, 可以去掉小的对象, 开就是开除的意思
- 闭操作- close, 先膨胀后腐蚀, 可以填充小的洞, 闭就是堵上的意思
- 梯度- Morphological Gradient, 膨胀减去腐蚀, 又称为基本梯度（其它还包括-内部梯度、方向梯度）
- 顶帽 – top hat, 顶帽 是原图像与开操作之间的差值图像
- 黑帽 – black hat, 黑帽是闭操作图像与源图像的差值图像
- CV_EXPORTS_W void morphologyEx( InputArray src, OutputArray dst,
                                int op, InputArray kernel,
                                Point anchor = Point(-1,-1), int iterations = 1,
                                int borderType = BORDER_CONSTANT,
                                const Scalar& borderValue = morphologyDefaultBorderValue() );其中op: CV_MOP_OPEN/ CV_MOP_CLOSE/ CV_MOP_GRADIENT / CV_MOP_TOPHAT/ CV_MOP_BLACKHAT 形态学操作类型
    代码: chapter_013.cpp

## 1.2.13. 提取水平与垂直线

- 说明: 形态学操作应用-提取水平与垂直线
- 输入图像彩色图像 imread
- 转换为灰度图像 – cvtColor
- 转换为二值图像 – adaptiveThreshold
- 定义结构元素
- 开操作 （腐蚀+膨胀）提取 水平与垂直线
- Mat hline = getStructuringElement(MORPH_RECT, Size(src.cppols / 16, 1), Point(-1, -1));// 水平结构元素
  - Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));// 垂直结构元素
  - Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));// 矩形结构
- void bitwise_not(InputArray src, OutputArray dst,
                              InputArray mask = noArray());像素取反
- void adaptiveThreshold( InputArray src, OutputArray dst,
                                     double maxValue, int adaptiveMethod,
                                     int thresholdType, int blockSize, double C );//转换为二值图像 
    代码: chapter_014.cpp

## 1.2.14. 上采样和降采样

- 说明: 图像上采样和降采样
- 一个图像金字塔是一系列的图像组合, 最底下一张是图像尺寸最大, 最上方的图像尺寸最小, 从空间上从上向下看就想一个古代的金字塔。
- 高斯金子塔 – 用来对图像进行降采样。高斯金子塔是从底向上, 逐层降采样得到。- 对当前层进行高斯模糊 - 删除当前层的偶数行与列。即可得到上一层的图像, 这样上一层跟下一层相比, 都只有它的1/4大小。
- 拉普拉斯金字塔 – 用来对图像进行上采样, 用来重建一张图片根据它的上层降采样图片
- 高斯不同(Difference of Gaussian-DOG): 就是把同一张图像在不同的参数下做高斯模糊之后的结果相减, 得到的输出图像。称为高斯不同(DOG), 高斯不同是图像的内在特征, 在灰度图像增强、角点检测中经常用到。
- 上采样(cv::pyrUp) – zoom in 放大
- 降采样 (cv::pyrDown) – zoom out 缩小
- subtract(InputArray src1, InputArray src2, OutputArray dst,
                           InputArray mask = noArray(), int dtype = -1);//取差值
- void normalize( InputArray src, InputOutputArray dst, double alpha = 1, double beta = 0,
                             int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());//归一化
- 代码: chapter_015.cpp

## 1.2.15. 基本阈yu值操作

- 说明: 基本阈yu值操作
- 阈值二值化    THRESH_BINARY        if f(x,y)>thresh,f(x,y)=maxval else f(x,y)=0
- 阈值反二值化    THRESH_BINARY_INV    if f(x,y)>thresh,f(x,y)=0 else f(x,y)=maxval
- 截断            THRESH_TRUNC        if f(x,y)>thresh,f(x,y)=thresh else f(x,y)=f(x,y)
- 阈值取零        THRESH_TOZERO        if f(x,y)>thresh,f(x,y)=f(x,y) else f(x,y)=0
- 阈值反取零    THRESH_TOZERO_INV   if f(x,y)>thresh,f(x,y)=0 else f(x,y)=f(x,y)
  - double threshold( InputArray src, OutputArray dst,
                               double thresh, double maxval, int type );//type=THRESH_BINARY...,thresh
    代码: chapter_016.cpp

## 1.2.16. 自定义线性滤波

- 说明: 自定义线性滤波
- Kernel: 本质上一个固定大小的矩阵数组, 其中心点称为锚点(anchor point),kernel就是可以自定义的卷积核
- 卷积: 把kernel放到像素数组之上, 求锚点周围覆盖的像素乘积之和（包括锚点）, 用来替换锚点覆盖下像素点值称为卷积处理。
- 常见kernel:Robert算子(二维)/Sobel算子(三维)/拉普拉斯算子(三维)
- filter2D方法:filter2D(
                Mat src, //输入图像
                Mat dst, // 模糊图像
                int depth, // 图像深度32/8
                Mat kernel, // 卷积核/模板
                Point anchor, // 锚点位置
                double delta, // 计算出来的像素+delta
                int borderType = BORDER_DEFAULT //边界体填充方式
    )
- 阈值反二值化    THRESH_BINARY_INV    if f(x,y)>thresh,f(x,y)=0 else f(x,y)=maxval
- 截断            THRESH_TRUNC        if f(x,y)>thresh,f(x,y)=thresh else f(x,y)=f(x,y)
- 阈值取零        THRESH_TOZERO        if f(x,y)>thresh,f(x,y)=f(x,y) else f(x,y)=0
- 阈值反取零    THRESH_TOZERO_INV   if f(x,y)>thresh,f(x,y)=0 else f(x,y)=f(x,y)
    代码: chapter_017.cpp

## 1.2.17. 卷积边缘

- 说明: 卷积处理边缘
- 图像卷积的时候边界像素, 不能被卷积操作, 原因在于边界像素没有完全跟kernel重叠, 所以当3x3滤波时候有1个像素的边缘没有被处理, 5x5滤波的时候有2个像素的边缘没有被处理。
- BORDER_DEFAULT: 默认处理方法, 在卷积开始之前增加边缘像素, 填充的像素值为0
- BORDER_CONSTANT – 填充边缘用指定像素值//!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
- BORDER_REPLICATE – 填充边缘像素用已知的边缘像素值。//!< `aaaaaa|abcdefgh|hhhhhhh`
- BORDER_WRAP – 用另外一边的像素来补偿填充//!< `cdefgh|abcdefgh|abcdefg`
- BORDER_REFLECT     = 2, //!< `fedcba|abcdefgh|hgfedcb`
- BORDER_REFLECT_101 = 4, //!< `gfedcb|abcdefgh|gfedcba`
- BORDER_TRANSPARENT = 5, //!< `uvwxyz|abcdefgh|ijklmno`
- void copyMakeBorder(InputArray src, OutputArray dst,
                                 int top, int bottom, int left, int right,
                                 int borderType, const Scalar& value = Scalar() );
    代码: chapter_018.cpp

## 1.2.18. Sobel算子

- 说明: Sobel算子, 卷积应用-图像边缘提取
- 边缘是什么 – 是像素值发生跃迁的地方, 是图像的显著特征之一, 在图像特征提取、对象检测、模式识别等方面都有重要的作用。
- 如何捕捉/提取边缘 – 对图像求它的一阶导数delta =  f(x) – f(x-1), delta越大, 说明像素在X方向变化越大, 边缘信号越强。
- Sobel算子:
  - 是离散微分算子（discrete differentiation operator）, 用来计算图像灰度的近似梯度
  - Soble算子功能集合高斯平滑和微分求导
  - 又被称为一阶微分算子, 求导算子, 在水平和垂直两个方向上求导, 得到图像X方法与Y方向梯度图像
- 求取导数的近似值, kernel=3时不是很准确, OpenCV使用改进版本Scharr函数
- cv::Sobel 
        水平梯度: $G_{x}=\left[\begin{array}{ccc}{-3} & {0} & {+3} \\ {-10} & {0} & {+10} \\ {-3} & {0} & {+3}\end{array}\right]$
        垂直梯度: $G_{y}=\left[\begin{array}{ccc}{-3} & {-10} & {-3} \\ {0} & {0} & {0} \\ {+3} & {+10} & {+3}\end{array}\right]$
        最终梯度1：$\mathrm{G}=\sqrt{\mathrm{G}_{\mathrm{x}}^{2}+\mathrm{G}_{\mathrm{y}}^{2}}$
        最终梯度2：$\mathrm{G}=\left|\mathrm{G}_{\mathrm{x}}\right|+\left|\mathrm{G}_{\mathrm{y}}\right|$
- cv::Scharr
- GaussianBlur( src, dst, Size(3,3), 0, 0, BORDER_DEFAULT );
- cvtColor( src,  gray, COLOR_RGB2GRAY );
- addWeighted( A, 0.5,B, 0.5, 0, AB);
- convertScaleAbs(A, B)// 计算图像A的像素绝对值, 输出到图像B
    代码: chapter_019.cpp 

## 1.2.19. Laplance算子

- 说明: Laplance算子,在二阶导数的时候, 最大变化处的值为零即边缘是零值。通过二阶导数计算, 依据此理论我们可以计算图像二阶导数, 提取边缘。
- 拉普拉斯算子(Laplance operator)->cv::Laplacian
- 处理流程：
  - 高斯模糊 – 去噪声GaussianBlur()
  - 转换为灰度图像cvtColor()
  - 拉普拉斯 – 二阶导数计算Laplacian()
  - 取绝对值convertScaleAbs()

## 1.2.20. 

## 1.2.21. 

## 1.2.22. 

## 1.2.23. 

## 1.2.24. 

## 1.2.25. 

## 1.2.26. 

## 1.2.27. 

## 1.2.28. 

## 1.2.29. 

## 1.2.30. 

## 1.2.31. 

## 1.2.32. 

## 1.2.33. 

## 1.2.34. 