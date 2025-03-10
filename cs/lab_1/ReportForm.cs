using System;
using System.Windows.Forms;

namespace CarManagementApp
{
    /// <summary>
    /// Форма для отображения отчёта о коллекции автомобилей.
    /// </summary>
    public partial class ReportForm : Form
    {
        /// <summary>
        /// Инициализирует новый экземпляр формы <see cref="ReportForm"/> с указанным текстом отчёта.
        /// </summary>
        /// <param name="report">Строка, содержащая текст отчёта, который будет отображаться в форме.</param>
        public ReportForm(string report)
        {
            InitializeComponent();
            txtReport.Text = report;
        }

        /// <summary>
        /// Обработчик события клика по кнопке закрытия формы.
        /// При вызове закрывает форму.
        /// </summary>
        /// <param name="sender">Объект, вызвавший событие (кнопка).</param>
        /// <param name="e">Аргументы события.</param>
        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
