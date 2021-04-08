
// #include <opencv2/highgui.hpp>
#include "data.h"
#include <opencv2/opencv.hpp>

// ���ܣ���ȡͼƬ���ݣ�����������255�������������µ�ͼƬ
// ����֪ʶ�㣺
//     1. ��ȡ���ص㣬�����ص���в�������ʶrows(��,height)��cols(��,width)��channel(ͨ��)
//     2. ��ȡͼƬ��չʾͼƬ���ƶ�ͼƬ

using namespace cv;

int main(int argc, char **argv) {
    // read image
    Mat image = imread(TEST1_JPG);
    if (image.data == NULL) {
        printf("open fail.");
        return -1;
    }

    Mat invertImage;
    image.copyTo(invertImage); //����һ��

    // ��ȡͼ�����
    int channels = image.channels();
    int rows = image.rows;
    int cols = image.cols * channels;
    if (image.isContinuous()) { //�ڴ��Ƿ����������ڶ���ԭ����ܲ���������������Ļ���Ч�ʻ��һЩ
        cols *= rows;
        rows = 1;
    }

    // ÿ�����ص��ÿ��ͨ��255ȡ��
    uchar *p1; //ָ��ԭͼ������
    uchar *p2; //ָ��ת��������λ��
    for (int row = 0; row < rows; row++) {
        p1 = image.ptr<uchar>(row); // ��ȡ����ָ��
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
    cvMoveWindow("My Invert Image", 600, 0); //�ƶ�λ��

    // �ر�
    waitKey(0);
    destroyWindow("My Test");
    destroyWindow("My Invert Image");
    return 0;
}