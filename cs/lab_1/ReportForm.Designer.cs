using System;
using System.Windows.Forms;

namespace CarManagementApp
{
    /// <summary>
    /// Частичная реализация формы <see cref="ReportForm"/>, содержащая автоматически сгенерированный дизайнерский код.
    /// </summary>
    partial class ReportForm
    {
        /// <summary>
        /// Контейнер компонентов, используемый для хранения экземпляров компонентов формы.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Текстовое поле для отображения содержимого отчёта.
        /// </summary>
        private System.Windows.Forms.TextBox txtReport;

        /// <summary>
        /// Кнопка, позволяющая закрыть форму отчёта.
        /// </summary>
        private System.Windows.Forms.Button btnClose;

        /// <summary>
        /// Освобождает неуправляемые и управляемые ресурсы, используемые формой.
        /// </summary>
        /// <param name="disposing">
        /// <c>true</c>, если необходимо освободить управляемые и неуправляемые ресурсы;
        /// <c>false</c>, если нужно освободить только неуправляемые ресурсы.
        /// </param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
                components.Dispose();
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Метод, инициализирующий компоненты формы. 
        /// Этот метод автоматически генерируется дизайнером Windows Forms и не должен изменяться вручную.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtReport = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtReport
            // 
            this.txtReport.Location = new System.Drawing.Point(12, 12);
            this.txtReport.Multiline = true;
            this.txtReport.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtReport.Name = "txtReport";
            this.txtReport.ReadOnly = true;
            this.txtReport.Size = new System.Drawing.Size(460, 300);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(397, 320);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 30);
            this.btnClose.Text = "Закрыть";
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // ReportForm
            // 
            this.ClientSize = new System.Drawing.Size(484, 361);
            this.Controls.Add(this.txtReport);
            this.Controls.Add(this.btnClose);
            this.Name = "ReportForm";
            this.Text = "Отчет";
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
    }
}
