#include "data.h"
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

// 实现图像的掩膜操作
// 掩膜操作就是利用掩膜矩阵重新计算每一个像素的值。计算方法如下：
// 假设计算A点像素值，掩膜矩阵是3X3，则以A点为圆心，取出一个3X3的矩阵，与掩膜矩阵求和，结果作为A点新的像素值。

using namespace cv;

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread(TEST1_JPG);
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", CV_WINDOW_AUTOSIZE);
    imshow("input image", src);

    int cols = (src.cols - 1) * src.channels();
    int offsetx = src.channels();
    int rows = src.rows;

    dst = Mat::zeros(src.size(), src.type());
    for (int row = 1; row < (rows - 1); row++) { //等价于filter2D处理
        const uchar *previous = src.ptr<uchar>(row - 1);
        const uchar *current = src.ptr<uchar>(row);
        const uchar *next = src.ptr<uchar>(row + 1);
        uchar *output = dst.ptr<uchar>(row);
        for (int col = offsetx; col < cols; col++) {
            output[col] = saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[col]));
        }
    }

    // double t = getTickCount();
    // Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    // filter2D(src, dst, src.depth(), kernel);
    // double timeconsume = (getTickCount() - t) / getTickFrequency();
    // printf("tim consume %.2f\n", timeconsume);

    namedWindow("contrast image demo", CV_WINDOW_AUTOSIZE);
    imshow("contrast image demo", dst);
    cvMoveWindow("contrast image demo", 600, 0);

    waitKey(0);
    return 0;
}