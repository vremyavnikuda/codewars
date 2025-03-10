using CarManagementApp.Models;
using System;
using System.Windows.Forms;
using System.ComponentModel;

namespace CarManagementApp
{
    public partial class CarEditForm : Form
    {
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public Car EditedCar { get; private set; }


        /// <summary>
        /// Инициализирует новый экземпляр формы <see cref="CarEditForm"/> для создания нового автомобиля.
        /// </summary>
        public CarEditForm()
        {
            InitializeComponent();
            EditedCar = new Car();
        }

        /// <summary>
        /// Инициализирует новый экземпляр формы <see cref="CarEditForm"/> для редактирования существующего автомобиля.
        /// </summary>
        /// <param name="car">Объект <see cref="Car"/>, данные которого будут отображаться и редактироваться в форме.</param>

        /// <summary>
        /// Инициализирует новый экземпляр формы <see cref="CarEditForm"/> для редактирования существующего автомобиля.
        /// </summary>
        /// <param name="car">Объект <see cref="Car"/>, данные которого будут отображаться и редактироваться в форме.</param>
        /// <remarks>
        /// В этом конструкторе копируются значения полей из объекта <see cref="Car"/> в соответствующие поля формы.
        /// </remarks>
        public CarEditForm(Car car)
        {
            InitializeComponent();
            EditedCar = car;
            txtBrand.Text = car.Brand;
            txtModel.Text = car.Model;
            numYear.Value = car.YearOfManufacture;
            numPower.Value = car.Power;
            numCost.Value = car.Cost;
        }

        /// <summary>
        /// Обработчик события клика по кнопке "Сохранить".
        /// Обновляет свойства изменяемого автомобиля на основе введенных данных и закрывает форму.
        /// </summary>
        /// <param name="sender">Объект, вызвавший событие (кнопка).</param>
        /// <param name="e">Аргументы события.</param>
        private void btnSave_Click(object sender, EventArgs e)
        {
            EditedCar.Brand = txtBrand.Text;
            EditedCar.Model = txtModel.Text;
            EditedCar.YearOfManufacture = (int)numYear.Value;
            EditedCar.Power = (int)numPower.Value;
            EditedCar.Cost = numCost.Value;
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}