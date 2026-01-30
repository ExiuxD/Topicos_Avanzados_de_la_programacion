// funciones.cpp
#include <iostream>
#include "Funciones.h"

using namespace cv;
using namespace std;

// Carga la imagen y la verifica
bool cargarImagen(const string& ruta, Mat& img) {

    img = imread(ruta);

    if (img.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return false;
    }

    cout << "Imagen cargada correctamente." << endl;
    return true;
}

// Muestra la imagen redimensionada
bool mostrarImagenRedimencionada(const string& ruta, int ancho, int alto) {

    Mat img = imread(ruta);
    if (img.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return true;
    }
    Mat img_resized;
    resize(img, img_resized, Size(ancho, alto));
    imshow("Imagen Redimensionada", img_resized);
    imshow("Imagen Original", img);
    waitKey(0);

}

// Muestra las dimensiones de la imagen
void mostrarDimensiones(const Mat& img) {
    cout << "Ancho: " << img.cols << endl;
    cout << "Alto : " << img.rows << endl;
    cout << "Canales: " << img.channels() << endl;
}


// Dibuja un rectángulo rojo, un círculo verde y un texto en la imagen
void dibujarFiguras(Mat& img) {

    // 1. Rectángulo rojo alrededor de la imagen
    int margenX = 100;
    int margenY = 100;

    rectangle(
        img,
        Point(margenX, margenY),
        Point(img.cols - margenX, img.rows - margenY),
        Scalar(0, 0, 255),
        3
    );

    // 2. Círculo verde en el centro
    Point centro(img.cols / 2, img.rows / 2);

    circle(
        img,
        centro,
        50,
        Scalar(0, 255, 0), // Verde
        3
    );

    // 3. Texto en la parte inferior
    string texto = "Ejercicio 3 - OpenCV";
int baseline = 0;

Size textSize = getTextSize(
    texto,
    FONT_HERSHEY_SIMPLEX,
    0.8,
    2,
    &baseline
);

Point posicion(
    20,
    img.rows - baseline - 10
);

putText(
    img,
    texto,
    posicion,
    FONT_HERSHEY_SIMPLEX,
    0.8,
    Scalar(0, 0, 0),
    2
);

	// Mostrar la imagen con las figuras
    imshow("Imagen Original", img);
	waitKey(0);

}