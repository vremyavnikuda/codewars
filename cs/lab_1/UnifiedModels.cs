using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.CompilerServices;
using System.Text.Json.Serialization;

namespace CarManagementApp.Models
{
    // Перечисления
    public enum CarType
    {
        Sedan,
        Hatchback,
        Universal,
        SUV,
        Coupe,
        Minivan,
        Pickup,
        Convertible
    }

    public enum FuelType
    {
        Gasoline,
        Diesel,
        Electric,
        Hybrid,
        LPG,
        CNG
    }

    public enum CarColor
    {
        Red,
        Blue,
        Green,
        Black,
        White,
        Silver,
        Yellow,
        Purple,
        Orange,
        Brown
    }

    // Интерфейсы
    public interface IPhotoContainer
    {
        List<PhotoInfo> Photos { get; }
        void AddPhoto(string path, string description);
        void RemovePhoto(int index);
    }

    public interface IFuelTracking
    {
        List<FuelRecord> FuelRecords { get; }
        void AddFuelRecord(DateTime date, double liters, decimal cost, double odometer);
        double CalculateAverageFuelConsumption();
    }

    public interface ILocationTracking
    {
        GeoLocation CurrentLocation { get; set; }
        List<GeoLocation> LocationHistory { get; }
        void UpdateLocation(GeoLocation location);
        double CalculateTotalDistance();
    }

    public interface IServiceable
    {
        void PerformMaintenance();
        bool NeedsService();
    }

    // Базовый абстрактный класс для транспортных средств
    [Serializable]
    public abstract class Vehicle : INotifyPropertyChanged
    {
        private Guid id;
        protected string brand;
        protected int power;
        protected decimal cost;
        protected List<DateTime> repairDates;
        protected int yearOfManufacture;
        protected double mileage;
        protected Color color;
        protected string vin;
        protected DateTime registrationDate;
        protected DateTime lastInspectionDate;
        protected bool isInsured;
        protected DateTime insuranceExpiryDate;

        /// <summary>
        /// Конструктор по умолчанию.
        /// </summary>
        /// <remarks>
        /// Инициализирует все поля значениями по умолчанию.
        /// </remarks>
        public Vehicle()
        {
            id = Guid.NewGuid();
            brand = "Неизвестно";
            power = 0;
            cost = 0;
            repairDates = new List<DateTime>();
            yearOfManufacture = DateTime.Now.Year;
            mileage = 0;
            color = Color.White;
            vin = string.Empty;
            registrationDate = DateTime.Now;
            lastInspectionDate = DateTime.Now;
            isInsured = false;
            insuranceExpiryDate = DateTime.Now;
        }

        /// <summary>
        /// Конструктор.
        /// </summary>
        /// <remarks>
        /// Инициализирует поля <see cref="Brand"/>, <see cref="Power"/> и <see cref="Cost"/>.
        /// </remarks>
        /// <param name="brand">Марка транспортного средства.</param>
        /// <param name="power">Мощность транспортного средства (л.с.).</param>
        /// <param name="cost">Стоимость транспортного средства (руб.).</param>
        public Vehicle(string brand, int power, decimal cost) : this()
        {
            this.brand = brand;
            this.power = power;
            this.cost = cost;
        }

        public Guid Id => id;

        public string Brand
        {
            get => brand;
            set => SetProperty(ref brand, value);
        }

        public int Power
        {
            get => power;
            set
            {
                if (value < 0)
                    throw new PowerNegativeException("Мощность не может быть отрицательной");
                SetProperty(ref power, value);
            }
        }

        public decimal Cost
        {
            get => cost;
            set
            {
                if (value < 0)
                    throw new CostNegativeException("Стоимость не может быть отрицательной");
                SetProperty(ref cost, value);
            }
        }

        public List<DateTime> RepairDates => repairDates;

        public int YearOfManufacture
        {
            get => yearOfManufacture;
            set
            {
                if (value < 1900 || value > DateTime.Now.Year)
                    throw new ArgumentOutOfRangeException("Год производства должен быть между 1900 и текущим годом");
                SetProperty(ref yearOfManufacture, value);
            }
        }

        public double Mileage
        {
            get => mileage;
            set
            {
                if (value < 0)
                    throw new ArgumentOutOfRangeException("Пробег не может быть отрицательным");
                SetProperty(ref mileage, value);
            }
        }

        [JsonIgnore]
        public Color Color
        {
            get => color;
            set => SetProperty(ref color, value);
        }

        public string ColorHex
        {
            get => ColorTranslator.ToHtml(color);
            set => Color = ColorTranslator.FromHtml(value);
        }

        public string VIN
        {
            get => vin;
            set => SetProperty(ref vin, value);
        }

        public DateTime RegistrationDate
        {
            get => registrationDate;
            set => SetProperty(ref registrationDate, value);
        }

        public DateTime LastInspectionDate
        {
            get => lastInspectionDate;
            set => SetProperty(ref lastInspectionDate, value);
        }

        public bool IsInsured
        {
            get => isInsured;
            set => SetProperty(ref isInsured, value);
        }

        public DateTime InsuranceExpiryDate
        {
            get => insuranceExpiryDate;
            set => SetProperty(ref insuranceExpiryDate, value);
        }

        public int Age => DateTime.Now.Year - yearOfManufacture;
        public bool NeedsInspection => (DateTime.Now - lastInspectionDate).TotalDays > 365;
        public bool InsuranceExpired => isInsured && DateTime.Now > insuranceExpiryDate;

        public DateTime this[int index]
        {
            get
            {
                if (index < 0 || index >= repairDates.Count)
                    throw new IndexOutOfRangeException("Индекс за пределами списка дат ремонта");
                return repairDates[index];
            }
        }

        public virtual void AddRepairDate(DateTime date)
        {
            repairDates.Add(date);
            OnPropertyChanged(nameof(RepairDates));
        }

        public virtual void RemoveRepairDate(DateTime date)
        {
            repairDates.Remove(date);
            OnPropertyChanged(nameof(RepairDates));
        }

        public virtual DateTime GetLastRepairDate() =>
            repairDates.Count == 0 ? DateTime.MinValue : repairDates[repairDates.Count - 1];

        public abstract string GetInfo();

        public virtual decimal CalculateDepreciation()
        {
            decimal ageDepreciation = Math.Min(0.5m, Age * 0.1m);
            return cost * ageDepreciation;
        }

        public virtual decimal CalculateMarketValue() => cost - CalculateDepreciation();

        public virtual decimal CalculateInsurancePremium()
        {
            decimal basePremium = cost * 0.05m;
            decimal ageFactor = 1 + (Age * 0.1m);
            return basePremium * ageFactor;
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        /// <summary>
        /// Вызывает событие <see cref="PropertyChanged"/>, если оно не равно null.
        /// </summary>
        /// <param name="propertyName">Имя свойства, которое изменилось. Если параметр не указан,
        /// то будет использовано имя свойства, вызвавшего это событие, полученное
        /// с помощью атрибута <see cref="CallerMemberNameAttribute"/>.</param>
        /// <remarks>В этом классе событие PropertyChanged вызывается для уведомления
        /// привязанных объектов о том, что значение свойства изменилось.
        /// </remarks>
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null) =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));

        /// <summary>
        /// Устанавливает новое значение для поля <paramref name="field"/>,
        /// если оно не равно текущему значению, и вызывает событие
        /// <see cref="PropertyChanged"/>, если оно не равно null.
        /// </summary>
        /// <typeparam name="T">Тип значения свойства.</typeparam>
        /// <param name="field">Поле, которое будет изменено.</param>
        /// <param name="value">Новое значение свойства.</param>
        /// <param name="propertyName">Имя свойства, которое изменилось.
        /// Если параметр не указан, то будет использовано имя свойства,
        /// вызвавшего это событие, полученное с помощью атрибута
        /// <see cref="CallerMemberNameAttribute"/>.</param>
        /// <returns>true, если значение было изменено, false - если
        /// значение не изменилось.</returns>
        /// <remarks>В этом классе метод SetProperty используется для
        /// уведомления привязанных объектов о том, что значение свойства
        /// изменилось.</remarks>
        protected bool SetProperty<T>(ref T field, T value, [CallerMemberName] string propertyName = null)
        {
            if (EqualityComparer<T>.Default.Equals(field, value))
                return false;
            field = value;
            OnPropertyChanged(propertyName);
            return true;
        }
    }

    // Класс для легковых автомобилей
    [Serializable]
    public class Car : Vehicle, IServiceable, IPhotoContainer, IFuelTracking, ILocationTracking, IComparable<Car>
    {
        private CarType carType;
        private FuelType fuelType;
        private string model;
        private int doors;
        private int seats;
        private string transmission;
        private List<PhotoInfo> photos;
        private List<FuelRecord> fuelRecords;
        private List<ServiceRecord> serviceHistory;
        private GeoLocation currentLocation;
        private List<GeoLocation> locationHistory;
        private DateTime nextMaintenanceDate;
        private double maintenanceIntervalKm;
        private string ownerName;
        private string licensePlate;

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="Car"/>,
        /// устанавливая значения по умолчанию для полей.
        /// </summary>
        public Car() : base()
        {
            carType = CarType.Sedan;
            fuelType = FuelType.Gasoline;
            model = "Неизвестно";
            doors = 4;
            seats = 5;
            transmission = "Механическая";
            photos = new List<PhotoInfo>();
            fuelRecords = new List<FuelRecord>();
            serviceHistory = new List<ServiceRecord>();
            currentLocation = new GeoLocation();
            locationHistory = new List<GeoLocation>();
            nextMaintenanceDate = DateTime.Now.AddMonths(6);
            maintenanceIntervalKm = 10000;
            ownerName = "Не указан";
            licensePlate = "Не указан";
        }

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="Car"/>,
        /// устанавливающий значения для полей <see cref="Brand"/>,
        /// <see cref="Model"/>, <see cref="Power"/>,
        /// <see cref="Cost"/>, <see cref="CarType"/>,
        /// <see cref="FuelType"/>, <see cref="YearOfManufacture"/>,
        /// <see cref="Mileage"/>, <see cref="Color"/>. Остальные поля
        /// устанавливаются значениями по умолчанию.
        /// </summary>
        /// <param name="brand">Марка автомобиля.</param>
        /// <param name="model">Модель автомобиля.</param>
        /// <param name="power">Мощность автомобиля, л.с.</param>
        /// <param name="cost">Стоимость автомобиля.</param>
        /// <param name="carType">Тип кузова автомобиля.</param>
        /// <param name="fuelType">Тип топлива автомобиля.</param>
        /// <param name="year">Год выпуска автомобиля.</param>
        /// <param name="mileage">Пробег автомобиля, км.</param>
        /// <param name="color">Цвет автомобиля.</param>
        public Car(string brand, string model, int power, decimal cost, CarType carType, FuelType fuelType,
            int year, double mileage, Color color)
            : base(brand, power, cost)
        {
            this.model = model;
            this.carType = carType;
            this.fuelType = fuelType;
            YearOfManufacture = year;
            Mileage = mileage;
            Color = color;
            doors = 4;
            seats = 5;
            transmission = "Механическая";
            photos = new List<PhotoInfo>();
            fuelRecords = new List<FuelRecord>();
            serviceHistory = new List<ServiceRecord>();
            currentLocation = new GeoLocation();
            locationHistory = new List<GeoLocation>();
            nextMaintenanceDate = DateTime.Now.AddMonths(6);
            maintenanceIntervalKm = 10000;
            ownerName = "Не указан";
            licensePlate = "Не указан";
        }

        // Для совместимости с формой редактирования
        public int Year
        {
            get => YearOfManufacture;
            set => YearOfManufacture = value;
        }

        public string Model
        {
            get => model;
            set => SetProperty(ref model, value);
        }

        public CarType CarType
        {
            get => carType;
            set => SetProperty(ref carType, value);
        }

        public FuelType FuelType
        {
            get => fuelType;
            set => SetProperty(ref fuelType, value);
        }

        public int Doors
        {
            get => doors;
            set
            {
                if (value < 1 || value > 6)
                    throw new ArgumentOutOfRangeException("Количество дверей должно быть от 1 до 6");
                SetProperty(ref doors, value);
            }
        }

        public int Seats
        {
            get => seats;
            set
            {
                if (value < 1 || value > 9)
                    throw new ArgumentOutOfRangeException("Количество мест должно быть от 1 до 9");
                SetProperty(ref seats, value);
            }
        }

        public string Transmission
        {
            get => transmission;
            set => SetProperty(ref transmission, value);
        }

        public List<PhotoInfo> Photos => photos;
        public List<FuelRecord> FuelRecords => fuelRecords;
        public List<ServiceRecord> ServiceHistory => serviceHistory;

        public GeoLocation CurrentLocation
        {
            get => currentLocation;
            set => SetProperty(ref currentLocation, value);
        }

        public List<GeoLocation> LocationHistory => locationHistory;

        public DateTime NextMaintenanceDate
        {
            get => nextMaintenanceDate;
            set => SetProperty(ref nextMaintenanceDate, value);
        }

        public double MaintenanceIntervalKm
        {
            get => maintenanceIntervalKm;
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("Интервал обслуживания должен быть положительным");
                SetProperty(ref maintenanceIntervalKm, value);
            }
        }

        public string OwnerName
        {
            get => ownerName;
            set => SetProperty(ref ownerName, value);
        }

        public string LicensePlate
        {
            get => licensePlate;
            set => SetProperty(ref licensePlate, value);
        }

        public string FullName => $"{Brand} {Model} ({YearOfManufacture})";

        public bool MaintenanceDue => DateTime.Now > nextMaintenanceDate ||
            (serviceHistory.Count > 0 ? (serviceHistory[serviceHistory.Count - 1].Odometer + maintenanceIntervalKm < Mileage) : true);

        /// <summary>
        /// Возвращает строку с подробной информацией об автомобиле.
        /// </summary>
        /// <returns>Строка с информацией об автомобиле.</returns>
        public override string GetInfo() =>
            $"Марка: {Brand}, Модель: {Model}, Тип: {CarType}, Мощность: {Power} л.с., Стоимость: {Cost:C}";

        /// <summary>
        /// Вычисляет сумму износа автомобиля.
        /// </summary>
        /// <remarks>
        /// Износ автомобиля вычисляется как максимальное значение из двух величин:
        /// - 10% от стоимости автомобиля за каждый год с момента выпуска до текущего года,
        /// - 20% от стоимости автомобиля за каждый 100,000 км пробега.
        /// </remarks>
        public override decimal CalculateDepreciation()
        {
            decimal ageDepreciation = Math.Min(0.7m, Age * 0.1m);
            decimal mileageDepreciation = Math.Min(0.5m, (decimal)(Mileage / 100000.0) * 0.2m);
            return Cost * Math.Max(ageDepreciation, mileageDepreciation);
        }

        /// <summary>
        /// Вычисляет страховой премиум для автомобиля.
        /// </summary>
        /// <remarks>
        /// Страховой премиум вычисляется как произведение следующих величин:
        /// - 5% от стоимости автомобиля,
        /// - 10% за каждый год с момента выпуска до текущего года,
        /// - 20% за каждый 100 л.с. мощности,
        /// - коэффициент, зависящий от типа автомобиля.
        /// </remarks>
        public override decimal CalculateInsurancePremium()
        {
            decimal basePremium = Cost * 0.05m;
            decimal ageFactor = 1 + (Age * 0.1m);
            decimal powerFactor = 1 + (Power / 100.0m) * 0.2m;
            decimal typeFactor = GetTypeInsuranceFactor();
            return basePremium * ageFactor * powerFactor * typeFactor;
        }

        /// <summary>
        /// Возвращает коэффициент страхования на основе типа автомобиля.
        /// </summary>
        /// <returns>Коэффициент страхования в зависимости от типа автомобиля.</returns>
        /// <remarks>
        /// Различные типы автомобилей имеют разные коэффициенты страхования:
        /// - Внедорожники (SUV) имеют коэффициент 1.2
        /// - Купе имеют коэффициент 1.3
        /// - Кабриолеты имеют коэффициент 1.4
        /// - Седаны имеют коэффициент 1.0
        /// - Все остальные типы имеют коэффициент 1.1
        /// </remarks>
        private decimal GetTypeInsuranceFactor()
        {
            switch (carType)
            {
                case CarType.SUV: return 1.2m;
                case CarType.Coupe: return 1.3m;
                case CarType.Convertible: return 1.4m;
                case CarType.Sedan: return 1.0m;
                default: return 1.1m;
            }
        }

        /// <summary>
        /// Выполняет плановое техническое обслуживание автомобиля.
        /// </summary>
        /// <remarks>
        /// Метод добавляет новый ServiceRecord в историю сервиса,
        /// устанавливающий текущую дату, описание, стоимость и пробег.
        /// Затем, он обновляет дату следующего обслуживания на 6 месяцев.
        /// </remarks>
        public void PerformMaintenance()
        {
            DateTime now = DateTime.Now;
            serviceHistory.Add(new ServiceRecord
            {
                Date = now,
                Description = "Плановое техническое обслуживание",
                Cost = CalculateMaintenanceCost(),
                Odometer = Mileage
            });
            nextMaintenanceDate = now.AddMonths(6);
            OnPropertyChanged(nameof(ServiceHistory));
            OnPropertyChanged(nameof(NextMaintenanceDate));
        }

        public bool NeedsService() => MaintenanceDue;

        /// <summary>
        /// Вычисляет стоимость технического обслуживания автомобиля.
        /// </summary>
        /// <remarks>
        /// Стоимость обслуживания вычисляется как произведение следующих величин:
        /// - 5000 рублей (базовая стоимость),
        /// - коэффициента возраста (1 + (возраст автомобиля в годах * 0.1)),
        /// - коэффициента типа автомобиля (1.3 для внедорожников и пикапов, 1.0 для других типов).
        /// </remarks>
        private decimal CalculateMaintenanceCost()
        {
            decimal baseCost = 5000;
            decimal ageFactor = 1 + (Age * 0.1m);
            decimal typeFactor = (carType == CarType.SUV || carType == CarType.Pickup) ? 1.3m : 1.0m;
            return baseCost * ageFactor * typeFactor;
        }

        /// <summary>
        /// Добавляет новый объект PhotoInfo в коллекцию Photos.
        /// </summary>
        /// <param name="path">Путь к файлу изображения.</param>
        /// <param name="description">Описание изображения.</param>
        /// <remarks>
        /// Новый объект PhotoInfo будет добавлен в конце списка Photos.
        /// </remarks>
        public void AddPhoto(string path, string description)
        {
            photos.Add(new PhotoInfo { Path = path, Description = description, DateAdded = DateTime.Now });
            OnPropertyChanged(nameof(Photos));
        }

        /// <summary>
        /// Удаляет объект PhotoInfo из коллекции Photos по его индексу.
        /// </summary>
        /// <param name="index">Индекс объекта PhotoInfo, который нужно удалить.</param>
        /// <remarks>
        /// Если <paramref name="index"/> находится в диапазоне от 0 до Photos.Count - 1,
        /// то объект PhotoInfo с указанным индексом будет удален из списка Photos.
        /// </remarks>
        public void RemovePhoto(int index)
        {
            if (index >= 0 && index < photos.Count)
            {
                photos.RemoveAt(index);
                OnPropertyChanged(nameof(Photos));
            }
        }

        /// <summary>
        /// Добавляет новый объект FuelRecord в коллекцию FuelRecords.
        /// </summary>
        /// <param name="date">Дата заправки.</param>
        /// <param name="liters">Количество литров, которое было заправлено.</param>
        /// <param name="cost">Стоимость заправки.</param>
        /// <param name="odometer">Пробег автомобиля на момент заправки.</param>
        /// <remarks>
        /// Новый объект FuelRecord будет добавлен в конце списка FuelRecords.
        /// </remarks>
        public void AddFuelRecord(DateTime date, double liters, decimal cost, double odometer)
        {
            if (liters <= 0)
                throw new ArgumentException("Количество литров должно быть положительным");
            if (cost <= 0)
                throw new ArgumentException("Стоимость должна быть положительной");
            if (odometer < Mileage)
                throw new ArgumentException("Пробег не может быть меньше текущего");
            fuelRecords.Add(new FuelRecord
            {
                Date = date,
                Liters = liters,
                Cost = cost,
                PricePerLiter = cost / (decimal)liters,
                Odometer = odometer
            });
            Mileage = odometer;
            OnPropertyChanged(nameof(FuelRecords));
        }

        /// <summary>
        /// Вычисляет средний расход топлива автомобиля на 100 км.
        /// </summary>
        /// <returns>Средний расход топлива в литрах на 100 км. Возвращает 0, если недостаточно данных.</returns>
        /// <remarks>
        /// Метод рассчитывает общее количество израсходованного топлива и общую пройденную дистанцию
        /// на основе записей топлива. Если количество записей меньше двух или общая дистанция равна нулю,
        /// возвращается 0.
        /// </remarks>
        public double CalculateAverageFuelConsumption()
        {
            if (fuelRecords.Count < 2)
                return 0;
            double totalFuel = 0;
            double totalDistance = 0;
            for (int i = 1; i < fuelRecords.Count; i++)
            {
                totalFuel += fuelRecords[i].Liters;
                totalDistance += fuelRecords[i].Odometer - fuelRecords[i - 1].Odometer;
            }
            return totalDistance == 0 ? 0 : (totalFuel / totalDistance) * 100;
        }

        /// <summary>
        /// Обновляет текущее местоположение автомобиля.
        /// </summary>
        /// <param name="location">Новое местоположение в формате <see cref="GeoLocation"/>.</param>
        /// <remarks>
        /// Добавляет предыдущее местоположение в историю, обновляет текущее местоположение
        /// и уведомляет об изменении истории местоположений.
        /// </remarks>
        public void UpdateLocation(GeoLocation location)
        {
            locationHistory.Add(currentLocation);
            CurrentLocation = location;
            OnPropertyChanged(nameof(LocationHistory));
        }

        /// <summary>
        /// Вычисляет общий пробег автомобиля на основе истории его местоположений.
        /// </summary>
        /// <returns>Общий пробег автомобиля в километрах. Возвращает 0, если история местоположений пуста.</returns>
        /// <remarks>
        /// Метод использует историю местоположений автомобиля, чтобы вычислить общий пробег.
        /// Он суммирует расстояния между соседними точками истории и возвращает общий результат.
        /// </remarks>
        public double CalculateTotalDistance()
        {
            double totalDistance = 0;
            for (int i = 1; i < locationHistory.Count; i++)
            {
                totalDistance += locationHistory[i - 1].CalculateDistance(locationHistory[i]);
            }
            return totalDistance;
        }

        /// <summary>
        /// Сравнивает текущий объект <see cref="Car"/> с другим объектом <see cref="Car"/>.
        /// </summary>
        /// <param name="other">Объект <see cref="Car"/>, с которым происходит сравнение.</param>
        /// <returns>
        /// Число, которое указывает на результат сравнения. Возвращает:
        /// <list type="bullet">
        /// <item>
        ///     0, если объекты равны;
        /// </item>
        /// <item>
        ///     отрицательное значение, если текущий объект меньше <paramref name="other"/>;
        /// </item>
        /// <item>
        ///     положительное значение, если текущий объект больше <paramref name="other"/>.
        /// </item>
        /// </list>
        /// </returns>
        /// <remarks>
        /// Метод сравнивает объекты <see cref="Car"/> по следующим критериям:
        /// <list type="bullet">
        /// <item>марка;</item>
        /// <item>модель;</item>
        /// <item>стоимость.</item>
        /// </list>
        /// </remarks>
        public int CompareTo(Car? other)
        {
            if (other == null) return 1;
            int brandComparison = this.Brand.CompareTo(other.Brand);
            if (brandComparison != 0) return brandComparison;
            int modelComparison = this.Model.CompareTo(other.Model);
            if (modelComparison != 0) return modelComparison;
            return this.Cost.CompareTo(other.Cost);
        }
    }

    [Serializable]
    public class PhotoInfo
    {
        public string Path { get; set; }
        public string Description { get; set; }
        public DateTime DateAdded { get; set; }
    }

    [Serializable]
    public class FuelRecord
    {
        public DateTime Date { get; set; }
        public double Liters { get; set; }
        public decimal Cost { get; set; }
        public decimal PricePerLiter { get; set; }
        public double Odometer { get; set; }
    }

    [Serializable]
    public class ServiceRecord
    {
        public DateTime Date { get; set; }
        public string Description { get; set; }
        public decimal Cost { get; set; }
        public double Odometer { get; set; }
    }

    [Serializable]
    public class GeoLocation
    {
        public double Latitude { get; set; }
        public double Longitude { get; set; }
        public DateTime Timestamp { get; set; }

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="GeoLocation"/>,
        /// устанавливая значения по умолчанию для полей:
        /// <list type="bullet">
        /// <item>широта - 0;</item>
        /// <item>долгота - 0;</item>
        /// <item>время - текущее время.</item>
        /// </list>
        /// </summary>
        public GeoLocation()
        {
            Latitude = 0;
            Longitude = 0;
            Timestamp = DateTime.Now;
        }

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="GeoLocation"/>,
        /// устанавливая значения для полей:
        /// <list type="bullet">
        /// <item>широта - <paramref name="latitude"/>&gt;;
        /// <item>долгота - <paramref name="longitude"/>&gt;;
        /// <item>время - текущее время.</item>
        /// </list>
        /// </summary>
        /// <param name="latitude">Широта местоположения.</param>
        /// <param name="longitude">Долгота местоположения.</param>
        public GeoLocation(double latitude, double longitude)
        {
            Latitude = latitude;
            Longitude = longitude;
            Timestamp = DateTime.Now;
        }

        /// <summary>
        /// Вычисляет расстояние в километрах между текущим местоположением
        /// и указанным в параметре <paramref name="other"/>.
        /// </summary>
        /// <param name="other">Местоположение, до которого будет вычислено расстояние.</param>
        /// <returns>Расстояние в километрах между текущим местоположением
        /// и указанным в параметре <paramref name="other"/>.</returns>
        /// <remarks>
        /// Метод использует формулу Хаверсина для вычисления расстояния
        /// между двумя точками на поверхности Земли.
        /// </remarks>
        public double CalculateDistance(GeoLocation other)
        {
            if (other == null) return 0;
            const double R = 6371.0;
            double lat1 = Latitude * Math.PI / 180;
            double lat2 = other.Latitude * Math.PI / 180;
            double dLat = (other.Latitude - Latitude) * Math.PI / 180;
            double dLon = (other.Longitude - Longitude) * Math.PI / 180;
            double a = Math.Sin(dLat / 2) * Math.Sin(dLat / 2) +
                       Math.Cos(lat1) * Math.Cos(lat2) *
                       Math.Sin(dLon / 2) * Math.Sin(dLon / 2);
            double c = 2 * Math.Atan2(Math.Sqrt(a), Math.Sqrt(1 - a));
            return R * c;
        }

        /// <summary>
        /// Возвращает строковое представление объекта <see cref="GeoLocation"/>.
        /// </summary>
        /// <returns>
        /// Строка, содержащая широту, долготу и временную метку в формате:
        /// "Широта: {Latitude}, Долгота: {Longitude}, Время: {Timestamp}".
        /// </returns>
        public override string ToString() =>
            $"Широта: {Latitude:F6}, Долгота: {Longitude:F6}, Время: {Timestamp}";
    }

    // Пользовательские исключения
    [Serializable]
    public class VehicleException : Exception
    {
        public VehicleException(string message) : base(message) { }
    }

    [Serializable]
    public class PowerNegativeException : VehicleException
    {
        public PowerNegativeException(string message) : base(message) { }
    }

    [Serializable]
    public class CostNegativeException : VehicleException
    {
        public CostNegativeException(string message) : base(message) { }
    }

    [Serializable]
    public class LicensePlateFormatException : VehicleException
    {
        public LicensePlateFormatException(string message) : base(message) { }
    }

    [Serializable]
    public class VINFormatException : VehicleException
    {
        public VINFormatException(string message) : base(message) { }
    }
}
