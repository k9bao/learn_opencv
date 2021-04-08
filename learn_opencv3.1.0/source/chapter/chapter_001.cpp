
// #include <opencv2/highgui.hpp>
#include "data.h"
#include <opencv2/opencv.hpp>

// 功能：读取图片数据，所有像素与255做减法，生成新的图片
// 掌握知识点：
//     1. 读取像素点，对像素点进行操作，认识rows(行,height)，cols(列,width)，channel(通道)
//     2. 读取图片，展示图片，移动图片

using namespace cv;

int main(int argc, char **argv) {
    // read image
    Mat image = imread(TEST1_JPG);
    if (image.data == NULL) {
        printf("open fail.");
        return -1;
    }

    Mat invertImage;
    image.copyTo(invertImage); //拷贝一份

    // 获取图像宽、高
    int channels = image.channels();
    int rows = image.rows;
    int cols = image.cols * channels;
    if (image.isContinuous()) { //内存是否连续，由于对齐原因可能不连续。如果连续的话，效率会高一些
        cols *= rows;
        rows = 1;
    }

    // 每个像素点的每个通道255取反
    uchar *p1; //指向原图像数据
    uchar *p2; //指向反转后存放数据位置
    for (int row = 0; row < rows; row++) {
        p1 = image.ptr<uchar>(row); // 获取像素指针
        p2 = invertImage.ptr<uchar>(row);
        for (int col = 0; col < cols; col++) {
            *p2 = 255 - *p1;
            p2++;
            p1++;
        }
    }

    // create windows
    namedWindow("My Test", CV_WINDOW_AUTOSIZE);
    namedWindow("My Invert Image", CV_WINDOW_AUTOSIZE);

    // display image
    imshow("My Test", image);
    imshow("My Invert Image", invertImage);
    cvMoveWindow("My Invert Image", 600, 0); //移动位置

    // 关闭
    waitKey(0);
    destroyWindow("My Test");
    destroyWindow("My Invert Image");
    return 0;
}