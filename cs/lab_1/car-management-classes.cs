using System;
using System.Collections.Generic;

// Абстрактный базовый класс для транспортных средств
public abstract class Vehicle
{
    // Защищенные поля класса
    protected string brand;
    protected int power;
    protected decimal cost;
    protected List<DateTime> repairDates;

    // Конструкторы
    public Vehicle()
    {
        brand = "Неизвестно";
        power = 0;
        cost = 0;
        repairDates = new List<DateTime>();
    }

    public Vehicle(string brand, int power, decimal cost)
    {
        this.brand = brand;
        this.power = power;
        this.cost = cost;
        repairDates = new List<DateTime>();
    }

    // Свойства
    public string Brand
    {
        get { return brand; }
        set { brand = value; }
    }

    public int Power
    {
        get { return power; }
        set 
        { 
            if (value < 0)
                throw new PowerNegativeException("Мощность не может быть отрицательной");
            power = value; 
        }
    }

    public decimal Cost
    {
        get { return cost; }
        set 
        { 
            if (value < 0)
                throw new CostNegativeException("Стоимость не может быть отрицательной");
            cost = value; 
        }
    }

    public List<DateTime> RepairDates
    {
        get { return repairDates; }
    }

    // Индексатор для доступа к датам ремонта
    public DateTime this[int index]
    {
        get
        {
            if (index < 0 || index >= repairDates.Count)
                throw new IndexOutOfRangeException("Индекс за пределами списка дат ремонта");
            return repairDates[index];
        }
    }

    // Виртуальные методы
    public virtual void AddRepairDate(DateTime date)
    {
        repairDates.Add(date);
    }

    public virtual void RemoveRepairDate(DateTime date)
    {
        repairDates.Remove(date);
    }

    public abstract string GetInfo();

    public virtual decimal CalculateDepreciation()
    {
        // Базовый расчет амортизации
        return cost * 0.1m;
    }
}

// Класс-наследник для легковых автомобилей
public class Car : Vehicle, IServiceable, IComparable<Car>
{
    private string carType;

    // Конструкторы
    public Car() : base()
    {
        carType = "Седан";
    }

    public Car(string brand, int power, decimal cost, string carType) : base(brand, power, cost)
    {
        this.carType = carType;
    }

    // Свойство
    public string CarType
    {
        get { return carType; }
        set { carType = value; }
    }

    // Переопределение виртуальных методов
    public override string GetInfo()
    {
        return $"Марка: {brand}, Тип: {carType}, Мощность: {power} л.с., Стоимость: {cost:C}";
    }

    public override decimal CalculateDepreciation()
    {
        // Специфичный расчет амортизации для автомобиля
        return cost * 0.15m;
    }

    // Реализация методов интерфейса IServiceable
    public void PerformMaintenance()
    {
        Console.WriteLine($"Выполнено техническое обслуживание автомобиля {brand}");
    }

    public bool NeedsService()
    {
        // Проверяем, был ли ремонт за последние 6 месяцев
        if (repairDates.Count == 0)
            return true;

        DateTime lastRepair = repairDates[repairDates.Count - 1];
        return (DateTime.Now - lastRepair).TotalDays > 180;
    }

    // Реализация IComparable для сортировки автомобилей
    public int CompareTo(Car other)
    {
        if (other == null) return 1;
        return this.cost.CompareTo(other.cost);
    }
}

// Интерфейсы
public interface IServiceable
{
    void PerformMaintenance();
    bool NeedsService();
}

// Пользовательские исключения
public class VehicleException : Exception
{
    public VehicleException(string message) : base(message) { }
}

public class PowerNegativeException : VehicleException
{
    public PowerNegativeException(string message) : base(message) { }
}

public class CostNegativeException : VehicleException
{
    public CostNegativeException(string message) : base(message) { }
}

// Класс для хранения коллекции автомобилей
public class CarCollection
{
    private List<Car> cars;

    public CarCollection()
    {
        cars = new List<Car>();
    }

    public void AddCar(Car car)
    {
        cars.Add(car);
    }

    public bool RemoveCar(Car car)
    {
        return cars.Remove(car);
    }

    public Car GetCar(int index)
    {
        if (index < 0 || index >= cars.Count)
            throw new IndexOutOfRangeException("Индекс находится за пределами коллекции автомобилей");
        return cars[index];
    }

    public List<Car> GetAllCars()
    {
        return cars;
    }

    public int Count
    {
        get { return cars.Count; }
    }
}
