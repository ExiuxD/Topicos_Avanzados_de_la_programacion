// ============================================================
// PUNTO DE ENTRADA DEL PROGRAMA
// Aqui inicia la aplicacion Windows Forms
// ============================================================

#include "Persona.h"
#include "MainForm.h"  // Incluimos el formulario principal

using namespace System;
using namespace System::Windows::Forms;
using namespace Streams_m;  // Namespace de nuestro proyecto

// ============================================================
// Funcion main - Punto de inicio
// ============================================================
[STAThread]  // Atributo necesario para aplicaciones Windows Forms
int main() {
    // Habilitamos estilos visuales modernos de Windows
    Application::EnableVisualStyles();

    // Establecemos compatibilidad con renderizado de texto
    Application::SetCompatibleTextRenderingDefault(false);

    // Creamos y ejecutamos el formulario principal
    MainForm^ formulario = gcnew MainForm();
    Application::Run(formulario);

    return 0;
}