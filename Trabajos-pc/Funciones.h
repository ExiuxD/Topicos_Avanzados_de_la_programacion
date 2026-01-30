#pragma once
// funciones.h
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <opencv2/opencv.hpp>
#include <string>

bool cargarYMostrarImagen(
    const std::string& ruta,
    int ancho,
    int alto
);
#endif
