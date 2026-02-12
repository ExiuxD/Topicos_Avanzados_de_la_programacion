using OpenCvSharp;
using OpenCvSharp.Extensions;
using System;
using System.Drawing;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using CvPoint = OpenCvSharp.Point;  // Alias para OpenCvSharp
using CvPoint2f = OpenCvSharp.Point2f;  // Alias para Point2f

namespace OpenCVImageProcessor
{
    public partial class Form1 : Form
    {
        // Variables para las imágenes
        private Mat imagenOriginal;
        private Mat imagenProcesada;
        private bool imagenCargada = false;

        // Control de valor actual (puede ser TrackBar o NumericUpDown)
        private Control controlValorActual; // Control genérico
        private bool ignorarEventoValor = false; // Bandera para evitar bucles
        //Declarar el CheckBox aquí
        private CheckBox chkInvertir;

        private VideoCapture captura;          // Objeto de captura de video
        private bool camaraActiva = false;     // Estado de la cámara
        private System.Windows.Forms.Timer timerCamara; // Timer para frames
        private Mat frameActual;               // Frame actual de la cámara
        private bool procesandoFrame = false; // Evitar acumulación de frames
        //CancellationToken para detener limpio
        private CancellationTokenSource ctsCamara;

        public Form1()
        {
            InitializeComponent();

            // Inicializar timer de cámara (60 FPS aprox)
            timerCamara = new System.Windows.Forms.Timer();
            timerCamara.Interval = 33; // ~30 FPS
            timerCamara.Tick += (s, e) => TimerCamara_Tick(s, e);

        }

        // ============================================
        // EVENTO: Cargar Imagen
        // ============================================
        private void btnCargarImagen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Archivos de imagen|*.jpg;*.jpeg;*.png;*.bmp;*.tiff";
            openFileDialog.Title = "Seleccionar imagen";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                // Cargar imagen con OpenCV
                imagenOriginal = Cv2.ImRead(openFileDialog.FileName);

                if (!imagenOriginal.Empty())
                {
                    imagenCargada = true;
                    imagenProcesada = imagenOriginal.Clone();

                    // Mostrar en PictureBox
                    MostrarImagen(imagenOriginal);

                    // Seleccionar "Original" en el ComboBox
                    cmbFiltros.SelectedIndex = 0;

                    MessageBox.Show("Imagen cargada correctamente", "Éxito",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("Error al cargar la imagen", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }


        // ============================================
        // EVENTO: Cargar Camara
        // ============================================
        private void btnCamara_Click(object sender, EventArgs e)
        {
                if (!camaraActiva)
                {
                    // ENCENDER CÁMARA
                    IniciarCamara();
                }
                else
                {
                    // APAGAR CÁMARA
                    DetenerCamara();
                }
        }

        // ============================================
        // EVENTO: Cambiar filtro seleccionado
        // ============================================
        private void cmbFiltros_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (camaraActiva)
            {
                // En modo cámara: solo configurar controles, el timer aplica el filtro
                ConfigurarControles(cmbFiltros.SelectedIndex);
                return;
            }

            // Modo imagen (código anterior)
            if (!imagenCargada) return;

            int filtroSeleccionado = cmbFiltros.SelectedIndex;
            ConfigurarControles(filtroSeleccionado);

            if (filtroSeleccionado == 0 || filtroSeleccionado == 1)
            {
                AplicarFiltro(filtroSeleccionado);
            }
        }

        // ============================================
        // EVENTO: TrackBar cambió de valor
        // ============================================
        private void trackBarValor_Scroll(object sender, EventArgs e)
        {
            if (!imagenCargada) return;

            int valor = trackBarValor.Value;
            lblValor.Text = "Valor: " + valor;

            // Reaplicar filtro con nuevo valor
            int filtroSeleccionado = cmbFiltros.SelectedIndex;
            AplicarFiltro(filtroSeleccionado, valor);
        }

        // ============================================
        // MÉTODO: Mostrar imagen en PictureBox
        // ============================================
        private void MostrarImagen(Mat imagen)
        {
            if (imagen.Empty()) return;

            // Convertir Mat a Bitmap
            Bitmap bmp = OpenCvSharp.Extensions.BitmapConverter.ToBitmap(imagen);
            pictureBoxImagen.Image?.Dispose(); // Liberar memoria anterior
            pictureBoxImagen.Image = bmp;
        }

        // ============================================
        // MÉTODO: Aplicar filtro seleccionado
        // ============================================
        private void AplicarFiltro(int tipoFiltro, int valor = -1, int valorExtra = 0)
        {
            if (imagenOriginal == null || imagenOriginal.Empty()) return;

            switch (tipoFiltro)
            {
                case 0: // Original
                    imagenProcesada = imagenOriginal.Clone();
                    break;

                case 1: // Escala de Grises
                    imagenProcesada = new Mat();
                    Cv2.CvtColor(imagenOriginal, imagenProcesada, ColorConversionCodes.BGR2GRAY);
                    // Convertir de vuelta a BGR para mantener consistencia
                    Cv2.CvtColor(imagenProcesada, imagenProcesada, ColorConversionCodes.GRAY2BGR);
                    break;

                case 2: // Binarización con inversión opcional
                    if (valor == -1) valor = 127;
                    using (Mat gris = new Mat())
                    {
                        Cv2.CvtColor(imagenOriginal, gris, ColorConversionCodes.BGR2GRAY);
                        imagenProcesada = new Mat();

                        // valorExtra = 0: Blanco/Negro, 1: Negro/Blanco
                        ThresholdTypes tipo = (valorExtra == 1) ?
                            ThresholdTypes.BinaryInv : ThresholdTypes.Binary;

                        Cv2.Threshold(gris, imagenProcesada, valor, 255, tipo);
                        Cv2.CvtColor(imagenProcesada, imagenProcesada, ColorConversionCodes.GRAY2BGR);
                    }
                    break;

                case 3: // Canny mejorado - bordes coloreados
                    if (valor == -1) valor = 100;
                    using (Mat gris = new Mat())
                    using (Mat bordes = new Mat())
                    {
                        Cv2.CvtColor(imagenOriginal, gris, ColorConversionCodes.BGR2GRAY);
                        Cv2.Canny(gris, bordes, valor, valor * 2);

                        // Crear imagen verde con solo los bordes
                        imagenProcesada = new Mat(imagenOriginal.Size(), MatType.CV_8UC3, new Scalar(0, 0, 0));

                        // Poner bordes en color verde neón
                        Mat[] canales = new Mat[3];
                        canales[0] = new Mat(imagenOriginal.Size(), MatType.CV_8UC1, new Scalar(0)); // B
                        canales[1] = bordes.Clone(); // G - bordes en verde
                        canales[2] = new Mat(imagenOriginal.Size(), MatType.CV_8UC1, new Scalar(0)); // R

                        Cv2.Merge(canales, imagenProcesada);

                        // Superponer sobre imagen original con transparencia
                        Cv2.AddWeighted(imagenOriginal, 0.6, imagenProcesada, 0.4, 0, imagenProcesada);

                        foreach (var c in canales) c.Dispose();
                    }
                    break;

                case 4: // Gaussian Blur con kernel visible
                    if (valor == -1) valor = 15;
                    if (valor % 2 == 0) valor++; // Asegurar impar

                    imagenProcesada = new Mat();
                    Cv2.GaussianBlur(imagenOriginal, imagenProcesada,
                        new OpenCvSharp.Size(valor, valor), 0);

                    // Agregar texto indicando el tamaño del kernel
                    string texto = $"Kernel: {valor}x{valor}";
                    Cv2.PutText(imagenProcesada, texto,
                        new OpenCvSharp.Point(10, 30),
                        HersheyFonts.HersheySimplex,
                        0.7, new Scalar(0, 255, 0), 2);
                    break;

                case 5: // Rotación completa sin cortar
                    if (valor == -1) valor = 45;

                    double angulo = valor * Math.PI / 180.0;

                    int w = imagenOriginal.Cols;
                    int h = imagenOriginal.Rows;

                    // Calcular nuevo tamaño
                    double cos = Math.Abs(Math.Cos(angulo));
                    double sin = Math.Abs(Math.Sin(angulo));

                    int nuevoW = (int)(w * cos + h * sin);
                    int nuevoH = (int)(w * sin + h * cos);

                    // Asegurar que sean positivos y no cero
                    if (nuevoW < 1) nuevoW = 1;
                    if (nuevoH < 1) nuevoH = 1;

                    // Centro de la imagen original
                    Point2f centro = new Point2f(w / 2.0f, h / 2.0f);

                    // Crear matriz de rotación
                    using (Mat matRotacion = Cv2.GetRotationMatrix2D(centro, valor, 1.0))
                    {
                        // Ajustar traslación para centrar
                        matRotacion.At<double>(0, 2) += (nuevoW - w) / 2.0;
                        matRotacion.At<double>(1, 2) += (nuevoH - h) / 2.0;

                        // Aplicar rotación
                        imagenProcesada = new Mat();
                        Cv2.WarpAffine(imagenOriginal, imagenProcesada, matRotacion,
                            new OpenCvSharp.Size(nuevoW, nuevoH),
                            borderMode: BorderTypes.Constant,
                            borderValue: new Scalar(64, 64, 64)); // Fondo gris oscuro
                    }

                    // Agregar texto del ángulo
                    Cv2.PutText(imagenProcesada, $"Rotacion: {valor}°",
                        new OpenCvSharp.Point(10, 30),
                        HersheyFonts.HersheySimplex,
                        0.7, new Scalar(0, 255, 0), 2);
                    break;
            }

            MostrarImagen(imagenProcesada);
        }

        // ============================================
        // MÉTODO: Configurar TrackBar según filtro
        // ============================================
        private void ConfigurarControles(int tipoFiltro)
        {
            // Limpiar controles anteriores
            if (controlValorActual != null)
            {
                panelControles.Controls.Remove(controlValorActual);
                controlValorActual.Dispose();
                controlValorActual = null;
            }
            if (chkInvertir != null)
            {
                panelControles.Controls.Remove(chkInvertir);
                chkInvertir.Dispose();
                chkInvertir = null;
            }

            if (tipoFiltro == 0 || tipoFiltro == 1)
            {
                panelControles.Visible = false;
                return;
            }

            // Crear TrackBar
            TrackBar trackBar = new TrackBar();
            trackBar.Location = new System.Drawing.Point(10, 40);
            trackBar.Size = new System.Drawing.Size(300, 45);
            trackBar.TickStyle = TickStyle.BottomRight;

            // CheckBox para binarización
            if (tipoFiltro == 2)
            {
                chkInvertir = new CheckBox();
                chkInvertir.Text = "Invertir (Negro/Blanco)";
                chkInvertir.Location = new System.Drawing.Point(10, 90);
                chkInvertir.AutoSize = true;
                chkInvertir.CheckedChanged += (s, ev) => {
                    if (camaraActiva) return; // El timer maneja la actualización
                    if (!imagenCargada) return;
                    AplicarFiltro(2, trackBar.Value, chkInvertir.Checked ? 1 : 0);
                };
                panelControles.Controls.Add(chkInvertir);
            }

            // Configurar rangos
            switch (tipoFiltro)
            {
                case 2: // Binarización
                    trackBar.Minimum = 0;
                    trackBar.Maximum = 255;
                    trackBar.Value = 127;
                    trackBar.TickFrequency = 16;
                    lblValor.Text = "Umbral: 127";
                    break;

                case 3: // Canny
                    trackBar.Minimum = 10;
                    trackBar.Maximum = 200;
                    trackBar.Value = 100;
                    trackBar.TickFrequency = 20;
                    lblValor.Text = "Umbral Canny: 100";
                    break;

                case 4: // Gaussian
                    trackBar.Minimum = 1;
                    trackBar.Maximum = 51;
                    trackBar.Value = 15;
                    trackBar.TickFrequency = 5;
                    lblValor.Text = "Kernel: 15";
                    break;

                case 5: // Rotación
                    trackBar.Minimum = 0;
                    trackBar.Maximum = 360;
                    trackBar.Value = 45;
                    trackBar.TickFrequency = 30;
                    lblValor.Text = "Ángulo: 45°";
                    break;
            }

            controlValorActual = trackBar;

            // Evento Scroll (tiempo real)
            trackBar.Scroll += (s, ev) =>
            {
                if (!camaraActiva && (ignorarEventoValor || !imagenCargada)) return;

                int valor = ((TrackBar)s).Value;

                if (tipoFiltro == 4 && valor % 2 == 0)
                    valor++;

                // Actualizar label
                string textoBase = lblValor.Text.Split(':')[0];
                lblValor.Text = textoBase + ": " + valor + (tipoFiltro == 5 ? "°" : "");

                // Si no es cámara, aplicar filtro estático
                if (!camaraActiva)
                {
                    int extra = (tipoFiltro == 2 && chkInvertir != null && chkInvertir.Checked) ? 1 : 0;
                    AplicarFiltro(cmbFiltros.SelectedIndex, valor, extra);
                }
            };

            panelControles.Controls.Add(trackBar);
            panelControles.Size = new System.Drawing.Size(320, tipoFiltro == 2 ? 120 : 90);
            panelControles.Visible = true;

            // Aplicar inicial (solo modo imagen)
            if (!camaraActiva)
            {
                ignorarEventoValor = true;
                int valExtra = (tipoFiltro == 2 && chkInvertir != null && chkInvertir.Checked) ? 1 : 0;
                AplicarFiltro(tipoFiltro, trackBar.Value, valExtra);
                ignorarEventoValor = false;
            }
        }



        private void panelControles_Paint(object sender, PaintEventArgs e)
        {

        }


        private async void IniciarCamara()
        {
            try
            {
                // Verificar que no haya una cámara activa
                if (camaraActiva)
                {
                    DetenerCamara();
                    return;
                }

                captura = new VideoCapture(0);

                if (!captura.IsOpened())
                {
                    MessageBox.Show("No se pudo abrir la cámara", "Error");
                    return;
                }

                captura.Set(VideoCaptureProperties.FrameWidth, 320);
                captura.Set(VideoCaptureProperties.FrameHeight, 240);

                camaraActiva = true;
                ctsCamara = new CancellationTokenSource();
                frameActual = new Mat();

                btnCamara.Text = "Detener Cámara";
                btnCamara.BackColor = System.Drawing.Color.Red;
                btnCargarImagen.Enabled = false;

                await Task.Run(() => LoopCamara(ctsCamara.Token));
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
                DetenerCamara(); // Limpiar en caso de error
            }
        }

        private void LoopCamara(CancellationToken token)
        {
            while (!token.IsCancellationRequested && camaraActiva)
            {
                if (procesandoFrame)
                {
                    Thread.Sleep(5);
                    continue;
                }

                // Verificar que captura sigue existiendo
                if (captura == null || !captura.IsOpened()) break;

                captura.Read(frameActual);

                if (frameActual == null || frameActual.Empty()) continue;

                procesandoFrame = true;

                // Verificar que el formulario sigue válido antes de Invoke
                if (!this.IsHandleCreated || this.IsDisposed)
                {
                    procesandoFrame = false;
                    break;
                }

                try
                {
                    this.Invoke(new Action(() =>
                    {
                        if (!camaraActiva || this.IsDisposed)
                        {
                            procesandoFrame = false;
                            return;
                        }

                        int filtro = cmbFiltros.SelectedIndex;
                        Mat frameProcesado = AplicarFiltroATiempoReal(frameActual, filtro);

                        MostrarImagen(frameProcesado);

                        if (frameProcesado != frameActual)
                            frameProcesado?.Dispose();

                        procesandoFrame = false;
                    }));
                }
                catch (ObjectDisposedException)
                {
                    // El formulario se cerró, salir del loop
                    break;
                }

                Thread.Sleep(33);
            }
        }

        private void DetenerCamara()
        {
            camaraActiva = false;

            // VERIFICAR que ctsCamara no sea null antes de cancelar
            if (ctsCamara != null)
            {
                ctsCamara.Cancel();
                ctsCamara.Dispose();
                ctsCamara = null;
            }

            // Esperar un poco
            Thread.Sleep(100);

            // Liberar captura
            if (captura != null)
            {
                captura.Release();
                captura.Dispose();
                captura = null;
            }

            if (frameActual != null)
            {
                frameActual.Dispose();
                frameActual = null;
            }

            // Actualizar UI de forma segura
            if (this.IsHandleCreated && !this.IsDisposed)
            {
                this.Invoke(new Action(() => {
                    if (this.IsDisposed) return;

                    btnCamara.Text = "Abrir Cámara";
                    btnCamara.BackColor = System.Drawing.Color.Gray;
                    btnCargarImagen.Enabled = true;
                    pictureBoxImagen.Image = null;
                    cmbFiltros.SelectedIndex = 0;
                    panelControles.Visible = false;
                }));
            }
        }

        // TIMER: Procesar cada frame
        private void TimerCamara_Tick(object sender, EventArgs e)
        {
            if (!camaraActiva || captura == null) return;

            // Capturar frame
            captura.Read(frameActual);

            if (frameActual.Empty()) return;

            // Aplicar filtro seleccionado al frame
            int filtro = cmbFiltros.SelectedIndex;
            Mat frameProcesado = AplicarFiltroATiempoReal(frameActual, filtro);

            // Mostrar
            MostrarImagen(frameProcesado);

            // Liberar si no es el frame original
            if (frameProcesado != frameActual)
                frameProcesado?.Dispose();
        }

        // Versión optimizada para video (sin clones innecesarios)
        private Mat AplicarFiltroATiempoReal(Mat entrada, int tipoFiltro)
        {
            // Obtener valor actual del TrackBar si existe
            int valor = 127; // default
            if (controlValorActual is TrackBar tb)
            {
                valor = tb.Value;
            }

            Mat salida = new Mat();

            switch (tipoFiltro)
            {
                case 0: // Original
                    return entrada; // Sin procesar

                case 1: // Escala de Grises
                    Cv2.CvtColor(entrada, salida, ColorConversionCodes.BGR2GRAY);
                    Cv2.CvtColor(salida, salida, ColorConversionCodes.GRAY2BGR);
                    return salida;

                case 2: // Binarización
                    int extra = (chkInvertir != null && chkInvertir.Checked) ? 1 : 0;
                    using (Mat gris = new Mat())
                    {
                        Cv2.CvtColor(entrada, gris, ColorConversionCodes.BGR2GRAY);
                        ThresholdTypes tipo = (extra == 1) ? ThresholdTypes.BinaryInv : ThresholdTypes.Binary;
                        Cv2.Threshold(gris, salida, valor, 255, tipo);
                        Cv2.CvtColor(salida, salida, ColorConversionCodes.GRAY2BGR);
                    }
                    return salida;

                case 3: // Canny
                    using (Mat gris = new Mat())
                    using (Mat bordes = new Mat())
                    {
                        Cv2.CvtColor(entrada, gris, ColorConversionCodes.BGR2GRAY);
                        Cv2.Canny(gris, bordes, valor, valor * 2);
                        Cv2.CvtColor(bordes, salida, ColorConversionCodes.GRAY2BGR);
                    }
                    return salida;

                case 4: // Gaussian
                    if (valor % 2 == 0) valor++;
                    Cv2.GaussianBlur(entrada, salida, new OpenCvSharp.Size(valor, valor), 0);
                    return salida;

                case 5: // Rotación (simplificada para video)
                    double angulo = valor;
                    Point2f centro = new Point2f(entrada.Cols / 2.0f, entrada.Rows / 2.0f);
                    using (Mat rotMat = Cv2.GetRotationMatrix2D(centro, angulo, 1.0))
                    {
                        Cv2.WarpAffine(entrada, salida, rotMat, entrada.Size(),
                            borderMode: BorderTypes.Constant,
                            borderValue: new Scalar(0, 0, 0));
                    }
                    return salida;

                default:
                    return entrada;
            }
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            DetenerCamara();
            base.OnFormClosing(e);
        }
    }
}