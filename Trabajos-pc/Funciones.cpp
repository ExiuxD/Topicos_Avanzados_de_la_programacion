// funciones.cpp
#include <iostream>
#include "Funciones.h"

using namespace cv;
using namespace std;


// Primer ejercicio visto en clase en el cual se carga una imagen desde una ruta y
// se redimensiona a un ancho y alto especificados, mostrando ambas imágenes.
bool cargarYMostrarImagen(const string& ruta, int ancho, int alto) {
    Mat img_resized;

    // 1. Cargar imagen
    Mat img = imread(ruta);

    // 2. Verificar si se cargó correctamente
    if (img.empty()) {
        cout << "No se pudo cargar la imagen. Revisa la ruta o el nombre." << endl;
        return false;
    }

    // 3. Redimensionar
    resize(img, img_resized, Size(ancho, alto));

    // 4. Mostrar imágenes
    imshow("Imagen Original", img);
    imshow("Imagen Redimensionada", img_resized);
    waitKey(0);

    return true;
}