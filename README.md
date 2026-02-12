# Topicos_Avanzados_de_la_programacion
Repositorio personal de Mauricio Martínez Navarrete para la materia de Tópicos de la programación
En este repositorio se tienen dos carpetas de trabajo, por que?
Porque actualmente ocupo 2 computadoras con dos versiones diferentes de VS por ende sus archivos no son compatibles,
así que por ahora mientras instalo la misma versión de VS se quedará de esta manera

Aquí te dejo un README completo y profesional para tu repositorio de GitHub:

---


# 🖼️ OpenCV Image Processor

Aplicación de escritorio desarrollada en C# con Windows Forms que permite procesar imágenes y video en tiempo real utilizando OpenCV. El proyecto incluye una interfaz gráfica intuitiva con múltiples filtros de procesamiento de imagen y soporte para cámara web.

## 📋 Características Principales

- **Carga de imágenes**: Soporte para formatos JPG, PNG, BMP y TIFF
- **Procesamiento en tiempo real**: Aplicación de filtros con controles deslizantes (TrackBar)
- **Captura de video**: Integración con cámara web para procesamiento en vivo
- **5 filtros de imagen**: Escala de grises, binarización, detección de bordes, desenfoque gaussiano y rotación
- **Interfaz intuitiva**: Diseño limpio con controles dinámicos según el filtro seleccionado

## 🚀 Instalación y Uso

### Requisitos Previos
- Windows 10/11
- Visual Studio 2019 o superior
- .NET Framework 4.7.2 o superior
- Paquetes NuGet:
  - OpenCvSharp4
  - OpenCvSharp4.Extensions
  - OpenCvSharp4.runtime.win

### Compilación
1. Clona el repositorio
2. Abre la solución en Visual Studio
3. Restaura los paquetes NuGet
4. Compila y ejecuta (F5)

### Uso Básico
1. **Cargar imagen**: Haz clic en "Cargar Imagen" y selecciona un archivo
2. **Aplicar filtros**: Selecciona un filtro del menú desplegable
3. **Ajustar parámetros**: Usa el TrackBar para modificar los valores del filtro en tiempo real
4. **Usar cámara**: Haz clic en "Abrir Cámara" para procesar video en vivo

## 🎨 Filtros Disponibles

### 1. Escala de Grises
**Descripción**: Convierte la imagen a blanco y negro eliminando la información de color.

**Función matemática**: Promedio ponderado de los canales RGB

Gris = 0.299 × R + 0.587 × G + 0.114 × B


**Uso**: Reducción de complejidad, preparación para otros filtros, efectos artísticos.

---

### 2. Binarización (Umbral)
**Descripción**: Convierte la imagen en solo dos colores (negro y blanco) según un umbral.

**Función matemática**:

Si pixel > umbral → Blanco (255)
Si pixel ≤ umbral → Negro (0)


**Parámetro**: Umbral (0-255) - Controla el punto de corte entre negro y blanco

**Opción extra**: Inversión de colores (Negro/Blanco o Blanco/Negro)

**Uso**: Segmentación de objetos, reconocimiento de formas, OCR (reconocimiento óptico de caracteres).

---

### 3. Detección de Bordes (Canny)
**Descripción**: Identifica los contornos y bordes de los objetos en la imagen.

**Función matemática**:
1. **Suavizado gaussiano**: Reduce el ruido
2. **Gradiente de intensidad**: Detecta cambios bruscos de color
   
   Magnitud del gradiente = √(Gx² + Gy²)
   Dirección = arctan(Gy/Gx)
   
3. **Supresión de no-máximos**: Conserva solo los puntos más intensos del borde
4. **Umbral doble**: Clasifica bordes como fuertes o débiles

**Parámetro**: Umbral (10-200) - Sensibilidad de detección de bordes

**Uso**: Detección de objetos, reconocimiento de patrones, visión por computadora.

---

### 4. Desenfoque Gaussiano
**Descripción**: Suaviza la imagen reduciendo el ruido y los detalles finos.

**Función matemática**: Convolución con matriz gaussiana

G(x,y) = (1/2πσ²) × e^(-(x²+y²)/2σ²)


Donde:
- σ (sigma) controla la intensidad del desenfoque
- El tamaño del kernel debe ser impar (3, 5, 7, 15, etc.)

**Parámetro**: Tamaño del kernel (1-51) - Mayor valor = más desenfoque

**Uso**: Reducción de ruido, preparación para detección de bordes, efectos de profundidad de campo.

---

### 5. Rotación
**Descripción**: Gira la imagen alrededor de su centro manteniendo toda la información visible.

**Función matemática**: Matriz de transformación afín

[x']   [cos(θ)  -sin(θ)  tx]   [x]
[y'] = [sin(θ)   cos(θ)  ty] × [y]
[1 ]   [0        0       1 ]   [1]


Donde:
- θ = ángulo de rotación en grados
- tx, ty = traslación para centrar la imagen

**Cálculo de nuevo tamaño**:

nuevo_ancho = |ancho × cos(θ)| + |alto × sin(θ)|
nuevo_alto = |ancho × sin(θ)| + |alto × cos(θ)|


**Parámetro**: Ángulo (0-360°)

**Uso**: Corrección de orientación, efectos visuales, alineación de imágenes.

---

## 🎥 Modo Cámara

El sistema permite procesar video en tiempo real desde la cámara web:

- **Activación**: Botón "Abrir Cámara" / "Detener Cámara"
- **Procesamiento**: Los filtros se aplican a cada frame (30 FPS)
- **Controles dinámicos**: Ajusta parámetros mientras se reproduce el video
- **Multithreading**: El procesamiento ocurre en segundo plano para no bloquear la interfaz



## 🔧 Tecnologías Utilizadas

- **C#** - Lenguaje de programación principal
- **Windows Forms** - Framework de interfaz gráfica
- **OpenCV (OpenCvSharp)** - Biblioteca de procesamiento de imagen y visión por computadora
- **Doxygen** - Generación de documentación técnica

## 📚 Conceptos Matemáticos Aplicados

| Concepto | Aplicación en el Proyecto |
|----------|---------------------------|
| **Transformaciones lineales** | Rotación de imágenes |
| **Convolución** | Filtros de desenfoque y detección de bordes |
| **Gradientes** | Detección de cambios de intensidad (Canny) |
| **Umbralización** | Segmentación binaria |
| **Combinación lineal** | Conversión RGB a escala de grises |
| **Trigonometría** | Cálculo de dimensiones en rotación |

## 📝 Documentación

La documentación técnica completa se genera automáticamente con Doxygen:

1. Instala Doxygen desde https://www.doxygen.nl/
2. Ejecuta en la carpeta raíz:
   
   doxygen Doxyfile
   
3. Abre `docs/html/index.html` en tu navegador

## 👥 Autores

- [Tu nombre]
- [Nombre de compañeros si aplica]

## 📄 Licencia

Este proyecto es parte de la evaluación académica de la materia [Nombre de la materia].

---

## 🎯 Objetivos de Aprendizaje

- Implementación de algoritmos de procesamiento de imagen
- Manejo de bibliotecas de visión por computadora (OpenCV)
- Desarrollo de interfaces gráficas con Windows Forms
- Programación multihilo para aplicaciones en tiempo real
- Documentación técnica con Doxygen
- Control de versiones con Git/GitHub

