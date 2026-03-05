#ifndef PERSONA_H
#define PERSONA_H

// ============================================================
// ESTRUCTURA PERSONA
// Guarda los datos de una persona que se registraran
// ============================================================

using namespace System;  // Necesario para usar String de .NET

public ref class Persona {
public:
    // Propiedades de la persona (usamos String^ para manejar texto en .NET)
    String^ Nombres;           // Nombre(s) de la persona
    String^ ApellidoPaterno;   // Primer apellido
    String^ ApellidoMaterno;   // Segundo apellido
    String^ FechaNacimiento;   // Fecha de nacimiento (formato texto)
    String^ CURP;              // Clave Unica de Registro de Poblacion
    String^ Domicilio;         // Direccion completa

    // Constructor vacio - inicializa una persona sin datos
    Persona() {}

    // Constructor con parametros - inicializa con todos los datos
    Persona(String^ nom, String^ apPat, String^ apMat,
        String^ fecha, String^ curp, String^ dom) {
        Nombres = nom;
        ApellidoPaterno = apPat;
        ApellidoMaterno = apMat;
        FechaNacimiento = fecha;
        CURP = curp;
        Domicilio = dom;
    }

    // Metodo para guardar los datos en un archivo de texto
    // Recibe la ruta del archivo donde se guardara
    void GuardarEnArchivo(String^ rutaArchivo) {
        // StreamWriter permite escribir en archivos de texto
        // 'true' al final significa que agregara al final si el archivo existe (append)
        System::IO::StreamWriter^ escritor =
            gcnew System::IO::StreamWriter(rutaArchivo, true);

        // Escribimos cada dato en una linea separada
        escritor->WriteLine("========================================");
        escritor->WriteLine("NOMBRE(S): " + Nombres);
        escritor->WriteLine("APELLIDO PATERNO: " + ApellidoPaterno);
        escritor->WriteLine("APELLIDO MATERNO: " + ApellidoMaterno);
        escritor->WriteLine("FECHA DE NACIMIENTO: " + FechaNacimiento);
        escritor->WriteLine("CURP: " + CURP);
        escritor->WriteLine("DOMICILIO: " + Domicilio);
        escritor->WriteLine("========================================");
        escritor->WriteLine("");  // Linea en blanco para separar registros

        // Cerramos el archivo para liberar recursos
        escritor->Close();
    }
};

#endif