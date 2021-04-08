
#include <highgui.h>
#include <opencv2\opencv.hpp>

#include <assert.h>

using namespace cv;

void printMat(Mat &mat) {
    static int num = 1;
    printf("%03d:%x --- %d,%d,%d\n", num++, mat.data, mat.cols, mat.rows, mat.type());
}

//���re
void resizeAssert(int w, int h, int type, void *data, bool ret) {
    void *pSrc = malloc(200 * 200 * 3);
    memset(pSrc, 5, 200 * 200 * 3);
    Mat image(200, 200, CV_8UC3, pSrc);
    if (data == nullptr) {
        Mat dst(w, h, type);
        printMat(dst);
        void *p = dst.data;
        cv::resize(image, dst, cv::Size(100, 100), 0, 0);
        printMat(dst);
        assert(ret == (p == dst.data));
    } else {
        Mat dst(w, h, type, data);
        printMat(dst);
        cv::resize(image, dst, cv::Size(100, 100), 0, 0);
        printMat(dst);
        assert(ret == (data == dst.data));
    }
}

/*
���ۣ�resize�ڴ�������
resize( InputArray src, OutputArray dst,
Size dsize, double fx = 0, double fy = 0,
int interpolation = INTER_LINEAR );
1,���dst�ڴ����û�ָ����,��dst��cols��rows, type������Ԥ�ڵ�һ�£�����resize���·����ڴ档
2,���dst�ڴ���Mat�ڲ�����ģ���ֻҪdst��data��С��Ԥ�ڵĴ󣬾Ͳ����·����ڴ档
*/
int ResizeMemory(int argc, char **argv) {
    void *pDst = malloc(200 * 200 * 3);
    resizeAssert(100, 100, CV_8UC3, pDst, true);

    //same type, same w*h
    resizeAssert(50, 200, CV_8UC3, pDst, false);
    resizeAssert(200, 50, CV_8UC3, pDst, false);

    //same type, w*h < expect w*h
    resizeAssert(50, 100, CV_8UC3, pDst, false);
    resizeAssert(100, 50, CV_8UC3, pDst, false); //5

    //same type, w*h > expect w*h
    resizeAssert(100, 150, CV_8UC3, pDst, false);
    resizeAssert(150, 100, CV_8UC3, pDst, false);

    //not same type, w*h == expect w*h
    resizeAssert(100, 100, CV_8UC1, pDst, false);
    resizeAssert(100, 100, CV_8UC4, pDst, false); //9

    ///
    free(pDst);
    pDst = nullptr;                              //
    resizeAssert(100, 100, CV_8UC3, pDst, true); //10

    resizeAssert(50, 200, CV_8UC3, pDst, true); //ע�⣡����
    resizeAssert(200, 50, CV_8UC3, pDst, true); //ע�⣡����

    resizeAssert(50, 100, CV_8UC3, pDst, false);
    resizeAssert(100, 50, CV_8UC3, pDst, false);
    resizeAssert(100, 150, CV_8UC3, pDst, true); //15 //ע��!!!
    resizeAssert(150, 100, CV_8UC3, pDst, true); //ע��!!!

    resizeAssert(100, 100, CV_8UC1, pDst, false);
    resizeAssert(100, 100, CV_8UC4, pDst, true); //18  //ע��!!!
                                                 // �ر�
    return 0;
}

int ResizeSame(int argc, char **argv) {
    // read image
    Mat image = imread(TEST1_JPG);
    if (image.data == NULL) {
        printf("open fail.");
        return -1;
    }
    Mat dst;
    cv::resize(image, dst, cv::Size(100, 100), 0, 0);
}

int TestResize(int argc, char **argv) {
    return ResizeMemory(argc, argv);
}