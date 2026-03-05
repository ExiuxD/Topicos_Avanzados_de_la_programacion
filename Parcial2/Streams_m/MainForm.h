#ifndef MAINFORM_H
#define MAINFORM_H

#include "Persona.h"  // Incluimos nuestra estructura de datos

// ============================================================
// FORMULARIO PRINCIPAL
// Interfaz grafica para registrar personas
// ============================================================


    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;  // Para manejo de archivos
    namespace Streams_m {  // Cambia esto si tu proyecto tiene otro nombre

    public ref class MainForm : public System::Windows::Forms::Form {
    public:
        // Constructor del formulario
        MainForm(void) {
            InitializeComponent();  // Inicializa todos los controles visuales
        }

    protected:
        // Destructor - libera recursos cuando se cierra el formulario
        ~MainForm() {
            if (components) {
                delete components;
            }
        }

    private:
        // ============================================================
        // DECLARACION DE CONTROLES (Elementos visuales del formulario)
        // ============================================================

        // Contenedor principal que organiza los elementos
        System::ComponentModel::Container^ components;

        // Labels (etiquetas de texto)
        Label^ lblTitulo;           // Titulo del programa
        Label^ lblNombres;          // Etiqueta "Nombre(s)"
        Label^ lblApellidoPaterno;  // Etiqueta "Apellido Paterno"
        Label^ lblApellidoMaterno;  // Etiqueta "Apellido Materno"
        Label^ lblFechaNac;         // Etiqueta "Fecha de Nacimiento"
        Label^ lblCURP;             // Etiqueta "CURP"
        Label^ lblDomicilio;        // Etiqueta "Domicilio"

        // TextBox (campos de entrada de texto)
        TextBox^ txtNombres;           // Campo para nombres
        TextBox^ txtApellidoPaterno;   // Campo para apellido paterno
        TextBox^ txtApellidoMaterno;   // Campo para apellido materno
        TextBox^ txtFechaNac;          // Campo para fecha de nacimiento
        TextBox^ txtCURP;              // Campo para CURP
        TextBox^ txtDomicilio;         // Campo para domicilio

        // Botones
        Button^ btnGuardar;   // Boton para guardar datos
        Button^ btnLimpiar;   // Boton para limpiar campos

        // ============================================================
        // INICIALIZACION DE COMPONENTES (Diseño visual)
        // ============================================================

        void InitializeComponent(void) {
            // Creacion de controles
            this->lblTitulo = gcnew Label();
            this->lblNombres = gcnew Label();
            this->lblApellidoPaterno = gcnew Label();
            this->lblApellidoMaterno = gcnew Label();
            this->lblFechaNac = gcnew Label();
            this->lblCURP = gcnew Label();
            this->lblDomicilio = gcnew Label();

            this->txtNombres = gcnew TextBox();
            this->txtApellidoPaterno = gcnew TextBox();
            this->txtApellidoMaterno = gcnew TextBox();
            this->txtFechaNac = gcnew TextBox();
            this->txtCURP = gcnew TextBox();
            this->txtDomicilio = gcnew TextBox();

            this->btnGuardar = gcnew Button();
            this->btnLimpiar = gcnew Button();

            // SuspendLayout evita parpadeos mientras se crean los controles
            this->SuspendLayout();

            // ------------------------------------------------------------
            // CONFIGURACION DEL FORMULARIO PRINCIPAL
            // ------------------------------------------------------------
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(500, 450);  // Tamaño de ventana
            this->Text = L"Registro de Personas";  // Titulo de la ventana
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;  // Desactiva boton maximizar

            // ------------------------------------------------------------
            // TITULO
            // ------------------------------------------------------------
            this->lblTitulo->Text = L"REGISTRO DE PERSONAS";
            this->lblTitulo->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                14, System::Drawing::FontStyle::Bold);
            this->lblTitulo->Location = System::Drawing::Point(120, 20);
            this->lblTitulo->Size = System::Drawing::Size(280, 30);
            this->Controls->Add(this->lblTitulo);

            // ------------------------------------------------------------
            // CAMPOS DE ENTRADA (Labels y TextBox)
            // Posicion Y inicial: 70, incremento de 40 por cada campo
            // ------------------------------------------------------------

            // --- NOMBRE(S) ---
            this->lblNombres->Text = L"Nombre(s):";
            this->lblNombres->Location = System::Drawing::Point(30, 70);
            this->lblNombres->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblNombres);

            this->txtNombres->Location = System::Drawing::Point(160, 70);
            this->txtNombres->Size = System::Drawing::Size(300, 25);
            this->Controls->Add(this->txtNombres);

            // --- APELLIDO PATERNO ---
            this->lblApellidoPaterno->Text = L"Apellido Paterno:";
            this->lblApellidoPaterno->Location = System::Drawing::Point(30, 110);
            this->lblApellidoPaterno->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblApellidoPaterno);

            this->txtApellidoPaterno->Location = System::Drawing::Point(160, 110);
            this->txtApellidoPaterno->Size = System::Drawing::Size(300, 25);
            this->Controls->Add(this->txtApellidoPaterno);

            // --- APELLIDO MATERNO ---
            this->lblApellidoMaterno->Text = L"Apellido Materno:";
            this->lblApellidoMaterno->Location = System::Drawing::Point(30, 150);
            this->lblApellidoMaterno->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblApellidoMaterno);

            this->txtApellidoMaterno->Location = System::Drawing::Point(160, 150);
            this->txtApellidoMaterno->Size = System::Drawing::Size(300, 25);
            this->Controls->Add(this->txtApellidoMaterno);

            // --- FECHA DE NACIMIENTO ---
            this->lblFechaNac->Text = L"Fecha Nacimiento:";
            this->lblFechaNac->Location = System::Drawing::Point(30, 190);
            this->lblFechaNac->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblFechaNac);

            this->txtFechaNac->Location = System::Drawing::Point(160, 190);
            this->txtFechaNac->Size = System::Drawing::Size(300, 25);
            this->txtFechaNac->Text = L"DD/MM/AAAA";  // Texto de ayuda
            this->txtFechaNac->ForeColor = System::Drawing::Color::Gray;
            this->Controls->Add(this->txtFechaNac);

            // --- CURP ---
            this->lblCURP->Text = L"CURP:";
            this->lblCURP->Location = System::Drawing::Point(30, 230);
            this->lblCURP->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblCURP);

            this->txtCURP->Location = System::Drawing::Point(160, 230);
            this->txtCURP->Size = System::Drawing::Size(300, 25);
            this->txtCURP->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
            this->Controls->Add(this->txtCURP);

            // --- DOMICILIO ---
            this->lblDomicilio->Text = L"Domicilio:";
            this->lblDomicilio->Location = System::Drawing::Point(30, 270);
            this->lblDomicilio->Size = System::Drawing::Size(120, 25);
            this->Controls->Add(this->lblDomicilio);

            this->txtDomicilio->Location = System::Drawing::Point(160, 270);
            this->txtDomicilio->Size = System::Drawing::Size(300, 25);
            this->Controls->Add(this->txtDomicilio);

            // ------------------------------------------------------------
            // BOTONES
            // ------------------------------------------------------------

            // --- BOTON GUARDAR ---
            this->btnGuardar->Text = L"GUARDAR";
            this->btnGuardar->Location = System::Drawing::Point(120, 330);
            this->btnGuardar->Size = System::Drawing::Size(120, 40);
            this->btnGuardar->BackColor = System::Drawing::Color::LightGreen;
            this->btnGuardar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                10, System::Drawing::FontStyle::Bold);
            // Evento: cuando hagan clic, ejecuta el metodo btnGuardar_Click
            this->btnGuardar->Click += gcnew System::EventHandler(this, &MainForm::btnGuardar_Click);
            this->Controls->Add(this->btnGuardar);

            // --- BOTON LIMPIAR ---
            this->btnLimpiar->Text = L"LIMPIAR";
            this->btnLimpiar->Location = System::Drawing::Point(260, 330);
            this->btnLimpiar->Size = System::Drawing::Size(120, 40);
            this->btnLimpiar->BackColor = System::Drawing::Color::LightCoral;
            this->btnLimpiar->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                10, System::Drawing::FontStyle::Bold);
            this->btnLimpiar->Click += gcnew System::EventHandler(this, &MainForm::btnLimpiar_Click);
            this->Controls->Add(this->btnLimpiar);

            // Reanudamos el layout (dibujado de controles)
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        // ============================================================
        // EVENTOS (Acciones cuando el usuario interactua)
        // ============================================================

        // Evento cuando se hace clic en el boton GUARDAR
        void btnGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
            // Validamos que todos los campos tengan datos
            if (txtNombres->Text->Trim() == "" ||
                txtApellidoPaterno->Text->Trim() == "" ||
                txtApellidoMaterno->Text->Trim() == "" ||
                txtFechaNac->Text->Trim() == "" ||
                txtCURP->Text->Trim() == "" ||
                txtDomicilio->Text->Trim() == "") {

                // Si falta algun campo, mostramos mensaje de error
                MessageBox::Show("Por favor complete todos los campos.",
                    "Campos incompletos", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Creamos un objeto Persona con los datos de los TextBox
            Persona^ persona = gcnew Persona(
                txtNombres->Text->Trim(),
                txtApellidoPaterno->Text->Trim(),
                txtApellidoMaterno->Text->Trim(),
                txtFechaNac->Text->Trim(),
                txtCURP->Text->Trim()->ToUpper(),  // CURP siempre en mayusculas
                txtDomicilio->Text->Trim()
            );

            // Ruta del archivo donde guardaremos (en la carpeta del programa)
            String^ rutaArchivo = "registros_personas.txt";

            try {
                // Intentamos guardar en el archivo
                persona->GuardarEnArchivo(rutaArchivo);

                // Mensaje de exito
                MessageBox::Show("Datos guardados exitosamente en:\n" +
                    Path::GetFullPath(rutaArchivo),
                    "Exito", MessageBoxButtons::OK, MessageBoxIcon::Information);

                // Limpiamos los campos despues de guardar
                LimpiarCampos();
            }
            catch (Exception^ ex) {
                // Si hay error al guardar, mostramos el mensaje
                MessageBox::Show("Error al guardar: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // Evento cuando se hace clic en el boton LIMPIAR
        void btnLimpiar_Click(System::Object^ sender, System::EventArgs^ e) {
            LimpiarCampos();
        }

        // Metodo auxiliar para limpiar todos los campos de texto
        void LimpiarCampos() {
            txtNombres->Clear();
            txtApellidoPaterno->Clear();
            txtApellidoMaterno->Clear();
            txtFechaNac->Clear();
            txtCURP->Clear();
            txtDomicilio->Clear();

            // Devolvemos el foco al primer campo
            txtNombres->Focus();
        }
    };
}

#endif