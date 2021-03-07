
#include "opencv.h"

void testOpencv_h() {
    unsigned char I420[24] = {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,  //Y
        3, 3, 3, 3,  //U
        2, 2, 2, 2}; //V

    char *p = (char *)I420;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d ", p[i * 8 + j]);
        }
        printf("\n");
    }

    unsigned char NV12[24 * 4]; //4*4
    ImageInfo canvas{};
    canvas.data = (uintptr_t)NV12;
    canvas.scale = NV12ScaleCV;
    canvas.width = 8;
    canvas.height = 8;
    ImageInfo img{};
    img.data = (uintptr_t)I420;
    img.scale = I420ScaleCV;
    img.width = 4;
    img.height = 4;
    ImageRect rect{0, 0, 4, 4};
    NV12Draw(canvas, img, rect, false);
    p = (char *)canvas.data;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", p[i * 8 + j]);
        }
        printf("/n");
    }
}

int main(int argc, char **argv) {
    testOpencv_h();
    return 0;
}