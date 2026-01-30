#pragma once
// funciones.h
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <opencv2/opencv.hpp>
#include <string>

// Carga la imagen y la verifica
bool cargarImagen(const std::string& ruta, cv::Mat& img);

// Muestra la imagen redimensionada
bool mostrarImagenRedimencionada(const std::string& ruta, int ancho, int alto);

// Muestra las dimensiones de la imagen
void mostrarDimensiones(const cv::Mat& img);
#endif

// Dibuja figuras geométricas en la imagen
void dibujarFiguras(cv::Mat& img);

// Captura video de la cámara y muestra en escala de grises
void camaraEscalaGrises();

// Captura video de la cámara, dibuja figuras y muestra dimensiones
void camaraConEjercicios();

void camaraDobleVista();