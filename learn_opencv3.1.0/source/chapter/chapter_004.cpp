#include "data.h"
#include <iostream>
#include <opencv2/opencv.hpp>

// 1. 熟悉cv::mat创建及转换
// 2. 熟悉Scalar结构,标量/向量
// 3. 了解cvColor接口使用,颜色空间转换

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    Mat src;
    src = imread(TEST1_JPG);
    if (src.empty()) {
        cout << "could not load image..." << endl;
        return -1;
    }
    const char *inputName = "imput";
    const char *outputName = "output";
    namedWindow(inputName, CV_WINDOW_AUTOSIZE);
    namedWindow(outputName, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(outputName, 600, 0);

    imshow(inputName, src);

    Mat dst;
    dst = Mat(src.size(), src.type(), Scalar(127, 0, 255)); //Mat构造函数
    namedWindow(outputName, CV_WINDOW_AUTOSIZE);

    imshow(outputName, dst);
    waitKey(3000); //wait 3 seconds

    cvtColor(src, dst, CV_BGR2GRAY); //颜色空间转换
    printf("input image channels : %d\n", src.channels());
    printf("output image channels : %d\n", dst.channels());

    imshow(outputName, dst);
    waitKey(3000); //wait 3 seconds

    int cols = dst.cols; //列，width
    int rows = dst.rows; //行，height

    printf("rows : %d cols : %d\n", rows, cols);
    const uchar *firstRow = dst.ptr<uchar>(0);
    printf("fist pixel value : %d\n", *firstRow);

    Mat M(100, 100, CV_8UC1, Scalar(127)); //Mat构造函数
    //cout << "M =" << endl << M << endl;
    imshow(outputName, M);
    waitKey(3000); //wait 3 seconds

    Mat m1;                            //Mat构造函数
    m1.create(src.size(), src.type()); //Mat创建
    m1 = Scalar(0, 0, 255);
    imshow(outputName, m1);
    waitKey(3000); //wait 3 seconds

    Mat csrc;
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(src, csrc, -1, kernel); //掩膜处理

    imshow(outputName, csrc);
    waitKey(3000); //wait 3 seconds

    Mat m2 = Mat::eye(100, 100, CV_8UC1); //单位矩阵
    cout << "m2 =" << endl
         << m2 << endl;

    imshow(outputName, m2);
    waitKey(0);
    return 0;
}