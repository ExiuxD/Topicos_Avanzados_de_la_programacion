// ============================================================
// REGISTRO DE ESTUDIANTES - Windows Forms C++/CLI
// Lee archivo CSV y muestra datos en tabla con opcion de ordenar
// ============================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

// ============================================================
// NAMESPACE PARA CODIGO C++ NATIVO
// Aislamos el codigo estandar de C++/CLI para evitar conflictos
// ============================================================
namespace MiCodigoNativo {

    // ESTRUCTURA ESTUDIANTE
    struct Estudiante {
        string nombre;
        string apellidoPaterno;
        string apellidoMaterno;
        string matricula;
        string curp;
    };

    // FUNCION PARA LEER CSV
    vector<Estudiante> leerCSV(const string& nombreArchivo) {
        vector<Estudiante> lista;
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "Error: No se encontró el archivo 'estudiantes.csv'" << endl;
            cout << "Por favor créelo primero con los 10 estudiantes." << endl;
            return lista;
        }

        string linea;
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nom, apPat, apMat, mat, curp;

            getline(ss, nom, ',');
            getline(ss, apPat, ',');
            getline(ss, apMat, ',');
            getline(ss, mat, ',');
            getline(ss, curp, ',');

            Estudiante e;
            e.nombre = nom;
            e.apellidoPaterno = apPat;
            e.apellidoMaterno = apMat;
            e.matricula = mat;
            e.curp = curp;

            lista.push_back(e);
        }

        archivo.close();
        return lista;
    }

    // FUNCIONES DE COMPARACION PARA ORDENAR
    bool compararPorNombre(const Estudiante& a, const Estudiante& b) {
        return a.nombre < b.nombre;
    }

    bool compararPorApellidoPaterno(const Estudiante& a, const Estudiante& b) {
        return a.apellidoPaterno < b.apellidoPaterno;
    }

    bool compararPorApellidoMaterno(const Estudiante& a, const Estudiante& b) {
        return a.apellidoMaterno < b.apellidoMaterno;
    }

    bool compararPorMatricula(const Estudiante& a, const Estudiante& b) {
        return a.matricula < b.matricula;
    }

    bool compararPorCURP(const Estudiante& a, const Estudiante& b) {
        return a.curp < b.curp;
    }

    // VARIABLES GLOBALES
    vector<Estudiante> listaOriginal;
    vector<Estudiante> listaActual;
}

// ============================================================
// USINGS PARA WINDOWS FORMS (fuera del namespace nativo)
// ============================================================
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

// ============================================================
// FORMULARIO PRINCIPAL
// ============================================================
ref class MainForm : public Form {
private:
    DataGridView^ dgvTabla;
    Label^ lblTitulo;
    Button^ btnNombre;
    Button^ btnApPat;
    Button^ btnApMat;
    Button^ btnMatricula;
    Button^ btnCURP;
    Button^ btnOriginal;
    Label^ lblOrdenar;

public:
    MainForm() {
        InitializeComponent();
        CargarDatos();
    }

private:
    void InitializeComponent() {
        this->Text = L"Registro de Estudiantes - CSV";
        this->Size = System::Drawing::Size(950, 600);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->BackColor = Color::WhiteSmoke;

        lblTitulo = gcnew Label();
        lblTitulo->Text = L"DATOS DE ESTUDIANTES";
        lblTitulo->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
        lblTitulo->Location = System::Drawing::Point(300, 20);
        lblTitulo->Size = System::Drawing::Size(400, 40);
        lblTitulo->ForeColor = Color::DarkBlue;
        this->Controls->Add(lblTitulo);

        lblOrdenar = gcnew Label();
        lblOrdenar->Text = L"Ordenar por:";
        lblOrdenar->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        lblOrdenar->Location = System::Drawing::Point(30, 80);
        lblOrdenar->Size = System::Drawing::Size(100, 25);
        this->Controls->Add(lblOrdenar);

        int xBoton = 140;
        int anchoBoton = 130;

        btnNombre = CrearBoton(L"Nombre", xBoton, 80, anchoBoton);
        btnNombre->Click += gcnew EventHandler(this, &MainForm::btnNombre_Click);

        btnApPat = CrearBoton(L"A. Paterno", xBoton + 140, 80, anchoBoton);
        btnApPat->Click += gcnew EventHandler(this, &MainForm::btnApPat_Click);

        btnApMat = CrearBoton(L"A. Materno", xBoton + 280, 80, anchoBoton);
        btnApMat->Click += gcnew EventHandler(this, &MainForm::btnApMat_Click);

        btnMatricula = CrearBoton(L"Matricula", xBoton + 420, 80, anchoBoton);
        btnMatricula->Click += gcnew EventHandler(this, &MainForm::btnMatricula_Click);

        btnCURP = CrearBoton(L"CURP", xBoton + 560, 80, anchoBoton);
        btnCURP->Click += gcnew EventHandler(this, &MainForm::btnCURP_Click);

        btnOriginal = CrearBoton(L"Restaurar", xBoton + 700, 80, anchoBoton);
        btnOriginal->BackColor = Color::LightCoral;
        btnOriginal->Click += gcnew EventHandler(this, &MainForm::btnOriginal_Click);

        dgvTabla = gcnew DataGridView();
        dgvTabla->Location = System::Drawing::Point(30, 130);
        dgvTabla->Size = System::Drawing::Size(880, 400);
        dgvTabla->AllowUserToAddRows = false;
        dgvTabla->AllowUserToDeleteRows = false;
        dgvTabla->ReadOnly = true;
        dgvTabla->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        dgvTabla->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        dgvTabla->ColumnHeadersDefaultCellStyle->Font =
            gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        dgvTabla->ColumnHeadersDefaultCellStyle->BackColor = Color::LightBlue;
        dgvTabla->EnableHeadersVisualStyles = false;
        dgvTabla->AlternatingRowsDefaultCellStyle->BackColor = Color::LightGray;
        dgvTabla->RowHeadersVisible = false;

        this->Controls->Add(dgvTabla);
    }

    Button^ CrearBoton(String^ texto, int x, int y, int ancho) {
        Button^ btn = gcnew Button();
        btn->Text = texto;
        btn->Location = System::Drawing::Point(x, y);
        btn->Size = System::Drawing::Size(ancho, 35);
        btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Regular);
        btn->BackColor = Color::LightSteelBlue;
        btn->FlatStyle = FlatStyle::Flat;
        this->Controls->Add(btn);
        return btn;
    }

    void CargarDatos() {
        dgvTabla->Columns->Clear();
        dgvTabla->Rows->Clear();

        dgvTabla->Columns->Add("Nombre", L"Nombre(s)");
        dgvTabla->Columns->Add("ApPat", L"Apellido Paterno");
        dgvTabla->Columns->Add("ApMat", L"Apellido Materno");
        dgvTabla->Columns->Add("Matricula", L"Matricula");
        dgvTabla->Columns->Add("CURP", L"CURP");

        for (const auto& e : MiCodigoNativo::listaActual) {
            String^ nom = gcnew String(e.nombre.c_str());
            String^ apPat = gcnew String(e.apellidoPaterno.c_str());
            String^ apMat = gcnew String(e.apellidoMaterno.c_str());
            String^ mat = gcnew String(e.matricula.c_str());
            String^ curp = gcnew String(e.curp.c_str());

            dgvTabla->Rows->Add(nom, apPat, apMat, mat, curp);
        }

        lblTitulo->Text = L"DATOS DE ESTUDIANTES (" +
            MiCodigoNativo::listaActual.size().ToString() + L" registros)";
    }

    void btnNombre_Click(Object^ sender, EventArgs^ e) {
        sort(MiCodigoNativo::listaActual.begin(),
            MiCodigoNativo::listaActual.end(),
            MiCodigoNativo::compararPorNombre);
        CargarDatos();
    }

    void btnApPat_Click(Object^ sender, EventArgs^ e) {
        sort(MiCodigoNativo::listaActual.begin(),
            MiCodigoNativo::listaActual.end(),
            MiCodigoNativo::compararPorApellidoPaterno);
        CargarDatos();
    }

    void btnApMat_Click(Object^ sender, EventArgs^ e) {
        sort(MiCodigoNativo::listaActual.begin(),
            MiCodigoNativo::listaActual.end(),
            MiCodigoNativo::compararPorApellidoMaterno);
        CargarDatos();
    }

    void btnMatricula_Click(Object^ sender, EventArgs^ e) {
        sort(MiCodigoNativo::listaActual.begin(),
            MiCodigoNativo::listaActual.end(),
            MiCodigoNativo::compararPorMatricula);
        CargarDatos();
    }

    void btnCURP_Click(Object^ sender, EventArgs^ e) {
        sort(MiCodigoNativo::listaActual.begin(),
            MiCodigoNativo::listaActual.end(),
            MiCodigoNativo::compararPorCURP);
        CargarDatos();
    }

    void btnOriginal_Click(Object^ sender, EventArgs^ e) {
        MiCodigoNativo::listaActual = MiCodigoNativo::listaOriginal;
        CargarDatos();
    }
};

// ============================================================
// PUNTO DE ENTRADA
// ============================================================
[STAThread]
int main() {
    MiCodigoNativo::listaOriginal = MiCodigoNativo::leerCSV("estudiantes.csv");
    MiCodigoNativo::listaActual = MiCodigoNativo::listaOriginal;

    if (MiCodigoNativo::listaOriginal.empty()) {
        MessageBox::Show("No se pudieron cargar los datos del archivo CSV.",
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return 1;
    }

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm());

    return 0;
}