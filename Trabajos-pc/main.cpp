#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img_resized;
    // 1. Intentar cargar la imagen
    Mat img = imread("C:/Users/exiux/Downloads/Opencv_test_mau/x64/Debug/img/girasol.jpg");

    // 2. VERIFICAR PRIMERO si la imagen existe
    if (img.empty()) {
        cout << "No se pudo cargar la imagen. Revisa la ruta o el nombre." << endl;
        return -1;
    }

    // 3. Si existe, entonces redimensionar
    resize(img, img_resized, Size(636, 316));

    imshow("Imagen Original", img);
    imshow("Imagen de prueba", img_resized);
    waitKey(0);

    return 0;
}