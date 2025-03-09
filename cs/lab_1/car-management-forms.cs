using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace CarManagementApp
{
    public partial class MainForm : Form
    {
        private CarCollection carCollection;

        public MainForm()
        {
            InitializeComponent();
            carCollection = new CarCollection();
            UpdateCarList();
        }

        private void InitializeComponent()
        {
            this.menuStrip = new MenuStrip();
            this.fileToolStripMenuItem = new ToolStripMenuItem();
            this.addToolStripMenuItem = new ToolStripMenuItem();
            this.editToolStripMenuItem = new ToolStripMenuItem();
            this.deleteToolStripMenuItem = new ToolStripMenuItem();
            this.helpToolStripMenuItem = new ToolStripMenuItem();
            this.toolStrip = new ToolStrip();
            this.addButton = new ToolStripButton();
            this.editButton = new ToolStripButton();
            this.deleteButton = new ToolStripButton();
            this.carListBox = new ListBox();
            this.detailsPanel = new Panel();
            this.brandLabel = new Label();
            this.powerLabel = new Label();
            this.costLabel = new Label();
            this.typeLabel = new Label();
            this.repairDatesLabel = new Label();
            this.repairDatesListBox = new ListBox();

            // Настройка формы
            this.Text = "Управление автомобилями";
            this.Size = new Size(800, 600);

            // Настройка меню
            this.menuStrip.Items.AddRange(new ToolStripItem[] {
                fileToolStripMenuItem, helpToolStripMenuItem
            });
            
            this.fileToolStripMenuItem.Text = "Файл";
            this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] {
                addToolStripMenuItem, editToolStripMenuItem, deleteToolStripMenuItem
            });
            
            this.addToolStripMenuItem.Text = "Добавить";
            this.addToolStripMenuItem.Click += new EventHandler(AddCar);
            
            this.editToolStripMenuItem.Text = "Редактировать";
            this.editToolStripMenuItem.Click += new EventHandler(EditCar);
            
            this.deleteToolStripMenuItem.Text = "Удалить";
            this.deleteToolStripMenuItem.Click += new EventHandler(DeleteCar);
            
            this.helpToolStripMenuItem.Text = "Справка";
            this.helpToolStripMenuItem.Click += new EventHandler(ShowHelp);

            // Настройка панели инструментов
            this.toolStrip.Items.AddRange(new ToolStripItem[] {
                addButton, editButton, deleteButton
            });
            
            this.addButton.Text = "Добавить";
            this.addButton.Click += new EventHandler(AddCar);
            
            this.editButton.Text = "Редактировать";
            this.editButton.Click += new EventHandler(EditCar);
            
            this.deleteButton.Text = "Удалить";
            this.deleteButton.Click += new EventHandler(DeleteCar);

            // Настройка списка автомобилей
            this.carListBox.Location = new Point(10, 70);
            this.carListBox.Size = new Size(300, 450);
            this.carListBox.SelectedIndexChanged += new EventHandler(CarSelected);

            // Настройка панели деталей
            this.detailsPanel.Location = new Point(320, 70);
            this.detailsPanel.Size = new Size(450, 450);
            this.detailsPanel.BorderStyle = BorderStyle.FixedSingle;

            // Добавление элементов на панель деталей
            this.brandLabel.Location = new Point(10, 10);
            this.brandLabel.Size = new Size(430, 20);
            this.powerLabel.Location = new Point(10, 40);
            this.powerLabel.Size = new Size(430, 20);
            this.costLabel.Location = new Point(10, 70);
            this.costLabel.Size = new Size(430, 20);
            this.typeLabel.Location = new Point(10, 100);
            this.typeLabel.Size = new Size(430, 20);
            this.repairDatesLabel.Location = new Point(10, 130);
            this.repairDatesLabel.Text = "Даты ремонта:";
            this.repairDatesLabel.Size = new Size(430, 20);
            
            this.repairDatesListBox.Location = new Point(10, 160);
            this.repairDatesListBox.Size = new Size(430, 200);

            this.detailsPanel.Controls.AddRange(new Control[] {
                brandLabel, powerLabel, costLabel, typeLabel, 
                repairDatesLabel, repairDatesListBox
            });

            // Добавление элементов на форму
            this.Controls.AddRange(new Control[] {
                menuStrip, toolStrip, carListBox, detailsPanel
            });
            this.MainMenuStrip = this.menuStrip;
        }

        private void UpdateCarList()
        {
            carListBox.Items.Clear();
            foreach (Car car in carCollection.GetAllCars())
            {
                carListBox.Items.Add(car.GetInfo());
            }
        }

        private void ShowCarDetails(Car car)
        {
            if (car == null)
            {
                ClearDetails();
                return;
            }

            brandLabel.Text = $"Марка: {car.Brand}";
            powerLabel.Text = $"Мощность: {car.Power} л.с.";
            costLabel.Text = $"Стоимость: {car.Cost:C}";
            typeLabel.Text = $"Тип: {car.CarType}";

            repairDatesListBox.Items.Clear();
            foreach (DateTime date in car.RepairDates)
            {
                repairDatesListBox.Items.Add(date.ToShortDateString());
            }
        }

        private void ClearDetails()
        {
            brandLabel.Text = "";
            powerLabel.Text = "";
            costLabel.Text = "";
            typeLabel.Text = "";
            repairDatesListBox.Items.Clear();
        }

        private void CarSelected(object sender, EventArgs e)
        {
            if (carListBox.SelectedIndex >= 0)
            {
                Car selectedCar = carCollection.GetCar(carListBox.SelectedIndex);
                ShowCarDetails(selectedCar);
            }
        }

        private void AddCar(object sender, EventArgs e)
        {
            CarDialog dialog = new CarDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                carCollection.AddCar(dialog.Car);
                UpdateCarList();
            }
        }

        private void EditCar(object sender, EventArgs e)
        {
            if (carListBox.SelectedIndex >= 0)
            {
                Car selectedCar = carCollection.GetCar(carListBox.SelectedIndex);
                
                CarDialog dialog = new CarDialog(selectedCar);
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    // Подтверждение изменений
                    if (MessageBox.Show("Вы уверены, что хотите сохранить изменения?", 
                        "Подтверждение", MessageBoxButtons.YesNo) == DialogResult.Yes)
                    {
                        // Заменяем существующий автомобиль
                        carCollection.RemoveCar(selectedCar);
                        carCollection.AddCar(dialog.Car);
                        UpdateCarList();
                        ShowCarDetails(dialog.Car);
                    }
                }
            }
            else
            {
                MessageBox.Show("Выберите автомобиль для редактирования", "Предупреждение");
            }
        }

        private void DeleteCar(object sender, EventArgs e)
        {
            if (carListBox.SelectedIndex >= 0)
            {
                Car selectedCar = carCollection.GetCar(carListBox.SelectedIndex);
                
                if (MessageBox.Show($"Вы уверены, что хотите удалить {selectedCar.Brand}?", 
                    "Подтверждение удаления", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    carCollection.RemoveCar(selectedCar);
                    UpdateCarList();
                    ClearDetails();
                }
            }
            else
            {
                MessageBox.Show("Выберите автомобиль для удаления", "Предупреждение");
            }
        }

        private void ShowHelp(object sender, EventArgs e)
        {
            MessageBox.Show(
                "Приложение для управления автомобилями\n\n" +
                "- Добавить: создание нового автомобиля\n" +
                "- Редактировать: изменение данных выбранного автомобиля\n" +
                "- Удалить: удаление выбранного автомобиля\n\n" +
                "Для выбора автомобиля кликните на него в списке слева.",
                "Справка"
            );
        }

        // Новые поля для компонентов
        private MenuStrip menuStrip;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem addToolStripMenuItem;
        private ToolStripMenuItem editToolStripMenuItem;
        private ToolStripMenuItem deleteToolStripMenuItem;
        private ToolStripMenuItem helpToolStripMenuItem;
        private ToolStrip toolStrip;
        private ToolStripButton addButton;
        private ToolStripButton editButton;
        private ToolStripButton deleteButton;
        private ListBox carListBox;
        private Panel detailsPanel;
        private Label brandLabel;
        private Label powerLabel;
        private Label costLabel;
        private Label typeLabel;
        private Label repairDatesLabel;
        private ListBox repairDatesListBox;
    }

    public class CarDialog : Form
    {
        private Car car;
        private TextBox brandTextBox;
        private TextBox powerTextBox;
        private TextBox costTextBox;
        private ComboBox typeComboBox;
        private ListBox repairDatesListBox;
        private Button addDateButton;
        private Button removeDateButton;
        private Button okButton;
        private Button cancelButton;
        private ErrorProvider errorProvider;

        public Car Car { get { return car; } }

        public CarDialog()
        {
            InitializeComponent();
            car = new Car();
        }

        public CarDialog(Car existingCar)
        {
            InitializeComponent();
            car = new Car(existingCar.Brand, existingCar.Power, existingCar.Cost, existingCar.CarType);
            
            // Копируем даты ремонта
            foreach (DateTime date in existingCar.RepairDates)
            {
                car.AddRepairDate(date);
            }

            // Заполняем поля значениями
            brandTextBox.Text = car.Brand;
            powerTextBox.Text = car.Power.ToString();
            costTextBox.Text = car.Cost.ToString();
            typeComboBox.SelectedItem = car.CarType;

            // Заполняем список дат ремонта
            UpdateRepairDatesList();
        }

        private void InitializeComponent()
        {
            // Настройка формы
            this.Text = "Данные автомобиля";
            this.Size = new Size(400, 500);
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.StartPosition = FormStartPosition.CenterParent;

            // Создание компонентов
            Label brandLabel = new Label();
            brandLabel.Text = "Марка:";
            brandLabel.Location = new Point(20, 20);
            brandLabel.Size = new Size(100, 20);

            brandTextBox = new TextBox();
            brandTextBox.Location = new Point(130, 20);
            brandTextBox.Size = new Size(230, 20);

            Label powerLabel = new Label();
            powerLabel.Text = "Мощность (л.с.):";
            powerLabel.Location = new Point(20, 50);
            powerLabel.Size = new Size(100, 20);

            powerTextBox = new TextBox();
            powerTextBox.Location = new Point(130, 50);
            powerTextBox.Size = new Size(230, 20);

            Label costLabel = new Label();
            costLabel.Text = "Стоимость:";
            costLabel.Location = new Point(20, 80);
            costLabel.Size = new Size(100, 20);

            costTextBox = new TextBox();
            costTextBox.Location = new Point(130, 80);
            costTextBox.Size = new Size(230, 20);

            Label typeLabel = new Label();
            typeLabel.Text = "Тип:";
            typeLabel.Location = new Point(20, 110);
            typeLabel.Size = new Size(100, 20);

            typeComboBox = new ComboBox();
            typeComboBox.Location = new Point(130, 110);
            typeComboBox.Size = new Size(230, 20);
            typeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            typeComboBox.Items.AddRange(new object[] { "Седан", "Хэтчбек", "Универсал", "Внедорожник", "Купе" });
            typeComboBox.SelectedIndex = 0;

            Label repairDatesLabel = new Label();
            repairDatesLabel.Text = "Даты ремонта:";
            repairDatesLabel.Location = new Point(20, 140);
            repairDatesLabel.Size = new Size(100, 20);

            repairDatesListBox = new ListBox();
            repairDatesListBox.Location = new Point(20, 170);
            repairDatesListBox.Size = new Size(340, 150);

            addDateButton = new Button();
            addDateButton.Text = "Добавить дату";
            addDateButton.Location = new Point(20, 330);
            addDateButton.Size = new Size(160, 30);
            addDateButton.Click += new EventHandler(AddRepairDate);

            removeDateButton = new Button();
            removeDateButton.Text = "Удалить дату";
            removeDateButton.Location = new Point(200, 330);
            removeDateButton.Size = new Size(160, 30);
            removeDateButton.Click += new EventHandler(RemoveRepairDate);

            okButton = new Button();
            okButton.Text = "OK";
            okButton.DialogResult = DialogResult.OK;
            okButton.Location = new Point(200, 380);
            okButton.Size = new Size(75, 30);
            okButton.Click += new EventHandler(OkButton_Click);

            cancelButton = new Button();
            cancelButton.Text = "Отмена";
            cancelButton.DialogResult = DialogResult.Cancel;
            cancelButton.Location = new Point(285, 380);
            cancelButton.Size = new Size(75, 30);

            errorProvider = new ErrorProvider();

            // Добавление компонентов на форму
            this.Controls.AddRange(new Control[] {
                brandLabel, brandTextBox,
                powerLabel, powerTextBox,
                costLabel, costTextBox,
                typeLabel, typeComboBox,
                repairDatesLabel, repairDatesListBox,
                addDateButton, removeDateButton,
                okButton, cancelButton
            });

            this.AcceptButton = okButton;
            this.CancelButton = cancelButton;
        }

        private void UpdateRepairDatesList()
        {
            repairDatesListBox.Items.Clear();
            foreach (DateTime date in car.RepairDates)
            {
                repairDatesListBox.Items.Add(date.ToShortDateString());
            }
        }

        private void AddRepairDate(object sender, EventArgs e)
        {
            using (DateTimePicker picker = new DateTimePicker())
            {
                Form dateForm = new Form();
                dateForm.Text = "Выберите дату ремонта";
                dateForm.Size = new Size(300, 150);
                dateForm.FormBorderStyle = FormBorderStyle.FixedDialog;
                dateForm.StartPosition = FormStartPosition.CenterParent;
                dateForm.MaximizeBox = false;
                dateForm.MinimizeBox = false;

                Button okButton = new Button();
                okButton.DialogResult = DialogResult.OK;
                okButton.Text = "OK";
                okButton.Location = new Point(110, 70);
                okButton.Size = new Size(75, 30);

                picker.Format = DateTimePickerFormat.Short;
                picker.Location = new Point(10, 20);
                picker.Size = new Size(260, 20);

                dateForm.Controls.Add(picker);
                dateForm.Controls.Add(okButton);
                dateForm.AcceptButton = okButton;

                if (dateForm.ShowDialog() == DialogResult.OK)
                {
                    car.AddRepairDate(picker.Value.Date);
                    UpdateRepairDatesList();
                }
            }
        }

        private void RemoveRepairDate(object sender, EventArgs e)
        {
            if (repairDatesListBox.SelectedIndex >= 0)
            {
                DateTime selectedDate = car.RepairDates[repairDatesListBox.SelectedIndex];
                car.RemoveRepairDate(selectedDate);
                UpdateRepairDatesList();
            }
            else
            {
                MessageBox.Show("Выберите дату для удаления", "Предупреждение");
            }
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            // Проверка и сохранение данных
            bool isValid = true;
            errorProvider.Clear();

            if (string.IsNullOrWhiteSpace(brandTextBox.Text))
            {
                errorProvider.SetError(brandTextBox, "Марка не может быть пустой");
                isValid = false;
            }

            int power;
            if (!int.TryParse(powerTextBox.Text, out power) || power < 0)
            {
                errorProvider.SetError(powerTextBox, "Мощность должна быть положительным числом");
                isValid = false;
            }

            decimal cost;
            if (!decimal.TryParse(costTextBox.Text, out cost) || cost < 0)
            {
                errorProvider.SetError(costTextBox, "Стоимость должна быть положительным числом");
                isValid = false;
            }

            if (typeComboBox.SelectedIndex < 0)
            {
                errorProvider.SetError(typeComboBox, "Выберите тип автомобиля");
                isValid = false;
            }

            if (isValid)
            {
                try
                {
                    car.Brand = brandTextBox.Text;
                    car.Power = power;
                    car.Cost = cost;
                    car.CarType = typeComboBox.SelectedItem.ToString();
                    this.DialogResult = DialogResult.OK;
                }
                catch (VehicleException ex)
                {
                    MessageBox.Show(ex.Message, "Ошибка");
                    this.DialogResult = DialogResult.None;
                }
            }
            else
            {
                this.DialogResult = DialogResult.None;
            }
        }
    }
}
