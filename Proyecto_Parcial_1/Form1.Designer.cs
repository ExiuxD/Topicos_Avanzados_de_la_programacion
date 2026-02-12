using System;

namespace OpenCVImageProcessor
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnCargarImagen = new System.Windows.Forms.Button();
            this.btnCamara = new System.Windows.Forms.Button();
            this.cmbFiltros = new System.Windows.Forms.ComboBox();
            this.pictureBoxImagen = new System.Windows.Forms.PictureBox();
            this.lblValor = new System.Windows.Forms.Label();
            this.panelControles = new System.Windows.Forms.Panel();
            this.trackBarValor = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxImagen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarValor)).BeginInit();
            this.SuspendLayout();
            // 
            // btnCargarImagen
            // 
            this.btnCargarImagen.Location = new System.Drawing.Point(58, 383);
            this.btnCargarImagen.Name = "btnCargarImagen";
            this.btnCargarImagen.Size = new System.Drawing.Size(164, 23);
            this.btnCargarImagen.TabIndex = 0;
            this.btnCargarImagen.Text = "Cargar Imagen";
            this.btnCargarImagen.UseVisualStyleBackColor = true;
            this.btnCargarImagen.Click += new System.EventHandler(this.btnCargarImagen_Click);
            // 
            // btnCamara
            // 
            this.btnCamara.BackColor = System.Drawing.Color.White;
            this.btnCamara.Location = new System.Drawing.Point(576, 381);
            this.btnCamara.Name = "btnCamara";
            this.btnCamara.Size = new System.Drawing.Size(159, 23);
            this.btnCamara.TabIndex = 1;
            this.btnCamara.Text = "Abrir Cámara";
            this.btnCamara.UseVisualStyleBackColor = false;
            this.btnCamara.Click += new System.EventHandler(this.btnCamara_Click);
            // 
            // cmbFiltros
            // 
            this.cmbFiltros.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbFiltros.FormattingEnabled = true;
            this.cmbFiltros.Items.AddRange(new object[] {
            "Original",
            "Escala de Grises",
            "Binarización",
            "Canny (Bordes)",
            "Desenfoque Gaussiano",
            "Rotación"});
            this.cmbFiltros.Location = new System.Drawing.Point(299, 383);
            this.cmbFiltros.Name = "cmbFiltros";
            this.cmbFiltros.Size = new System.Drawing.Size(121, 21);
            this.cmbFiltros.TabIndex = 2;
            this.cmbFiltros.SelectedIndexChanged += new System.EventHandler(this.cmbFiltros_SelectedIndexChanged);
            // 
            // pictureBoxImagen
            // 
            this.pictureBoxImagen.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxImagen.Location = new System.Drawing.Point(74, 85);
            this.pictureBoxImagen.Name = "pictureBoxImagen";
            this.pictureBoxImagen.Size = new System.Drawing.Size(212, 213);
            this.pictureBoxImagen.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBoxImagen.TabIndex = 3;
            this.pictureBoxImagen.TabStop = false;
            // 
            // lblValor
            // 
            this.lblValor.AutoSize = true;
            this.lblValor.Location = new System.Drawing.Point(10, 15);
            this.lblValor.Name = "lblValor";
            this.lblValor.Size = new System.Drawing.Size(34, 13);
            this.lblValor.TabIndex = 0;
            this.lblValor.Text = "Valor:";
            // 
            // panelControles
            // 
            this.panelControles.Location = new System.Drawing.Point(415, 85);
            this.panelControles.Name = "panelControles";
            this.panelControles.Size = new System.Drawing.Size(320, 100);
            this.panelControles.TabIndex = 6;
            this.panelControles.Visible = false;
            this.panelControles.Paint += new System.Windows.Forms.PaintEventHandler(this.panelControles_Paint);
            // 
            // trackBarValor
            // 
            this.trackBarValor.Location = new System.Drawing.Point(214, 332);
            this.trackBarValor.Name = "trackBarValor";
            this.trackBarValor.Size = new System.Drawing.Size(300, 45);
            this.trackBarValor.TabIndex = 1;
            this.trackBarValor.Visible = false;
            this.trackBarValor.Scroll += new System.EventHandler(this.trackBarValor_Scroll);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.panelControles);
            this.Controls.Add(this.trackBarValor);
            this.Controls.Add(this.lblValor);
            this.Controls.Add(this.pictureBoxImagen);
            this.Controls.Add(this.cmbFiltros);
            this.Controls.Add(this.btnCamara);
            this.Controls.Add(this.btnCargarImagen);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxImagen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarValor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }





        #endregion

        private System.Windows.Forms.Button btnCargarImagen;
        private System.Windows.Forms.Button btnCamara;
        private System.Windows.Forms.ComboBox cmbFiltros;
        private System.Windows.Forms.PictureBox pictureBoxImagen;
        private System.Windows.Forms.Label lblValor;
        private System.Windows.Forms.Panel panelControles;
        internal System.Windows.Forms.TrackBar trackBarValor;
    }
}

