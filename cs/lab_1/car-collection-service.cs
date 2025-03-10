using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Text.Json;
using CarManagementApp.Models;

namespace CarManagementApp.Services
{
    // Интерфейс для сервиса автомобилей
    public interface ICarService
    {
        event EventHandler CollectionChanged;
        Task<IEnumerable<Car>> GetAllCarsAsync();
        Task<Car> GetCarByIdAsync(Guid id);
        Task AddCarAsync(Car car);
        Task UpdateCarAsync(Car car);
        Task DeleteCarAsync(Guid id);
        Task<IEnumerable<Car>> SearchCarsAsync(Expression<Func<Car, bool>> predicate);
        Task<IEnumerable<Car>> SortCarsAsync<TKey>(Expression<Func<Car, TKey>> keySelector, bool ascending = true);
        Task SaveDataAsync();
        Task LoadDataAsync();
        Task<bool> ExportToJsonAsync(string filePath);
        Task<bool> ImportFromJsonAsync(string filePath);
        Task<bool> ExportToXmlAsync(string filePath);
        Task<bool> ImportFromXmlAsync(string filePath);
        Task<string> GenerateReportAsync();
    }

    // Реализация сервиса для работы с коллекцией автомобилей
    public class CarService : ICarService
    {
        private List<Car> _cars;
        private string _dataFilePath;
        private ILogService _logService;

        // События
        public event EventHandler CollectionChanged;

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="CarService"/>.
        /// </summary>
        /// <param name="dataFilePath">Путь к файлу JSON, из которого загружаются данные.</param>
        /// <param name="logService">Сервис для логирования операций.</param>
        public CarService(string dataFilePath, ILogService logService)
        {
            _cars = new List<Car>();
            _dataFilePath = dataFilePath;
            _logService = logService;
        }

        /// <summary>
        /// Получает полный список автомобилей.
        /// </summary>
        /// <returns>Список автомобилей.</returns>
        public async Task<IEnumerable<Car>> GetAllCarsAsync()
        {
            return await Task.FromResult(_cars.ToList());
        }

        /// <summary>
        /// Получает автомобиль по его Id.
        /// </summary>
        /// <param name="id">Id автомобиля, который будет получен.</param>
        /// <returns>Объект автомобиля, если он найден, иначе null.</returns>
        /// <exception cref="KeyNotFoundException">Если автомобиль с указанным Id не найден.</exception>
        public async Task<Car> GetCarByIdAsync(Guid id)
        {
            return await Task.FromResult(_cars.FirstOrDefault(c => c.Id == id)!);
        }

        /// <summary>
        /// Добавляет автомобиль в коллекцию.
        /// </summary>
        /// <param name="car">Объект автомобиля, который будет добавлен.</param>
        /// <exception cref="ArgumentNullException">Если <paramref name="car"/> равен null.</exception>
        public async Task AddCarAsync(Car car)
        {
            if (car == null)
                throw new ArgumentNullException(nameof(car));

            _cars.Add(car);
            await _logService.LogInfoAsync($"Добавлен новый автомобиль: {car.Brand}");
            CollectionChanged?.Invoke(this, EventArgs.Empty);
        }

        /// <summary>
        /// Обновляет автомобиль с указанным Id.
        /// </summary>
        /// <param name="car">Объект автомобиля, содержащий обновленные данные.</param>
        /// <exception cref="ArgumentNullException">Если <paramref name="car"/> равен null.</exception>
        /// <exception cref="KeyNotFoundException">Если автомобиль с указанным Id не найден.</exception>
        public async Task UpdateCarAsync(Car car)
        {
            if (car == null)
                throw new ArgumentNullException(nameof(car));

            int index = _cars.FindIndex(c => c.Id == car.Id);
            if (index >= 0)
            {
                _cars[index] = car;
                await _logService.LogInfoAsync($"Обновлен автомобиль: {car.Brand}");
                CollectionChanged?.Invoke(this, EventArgs.Empty);
            }
            else
            {
                throw new KeyNotFoundException($"Автомобиль с ID {car.Id} не найден");
            }
        }

        /// <summary>
        /// Удаляет автомобиль из коллекции по указанному идентификатору.
        /// </summary>
        /// <param name="id">Идентификатор автомобиля, который нужно удалить.</param>
        /// <exception cref="KeyNotFoundException">Выбрасывается, если автомобиль с указанным идентификатором не найден.</exception>
        /// <remarks>
        /// Если автомобиль успешно удален, генерируется событие CollectionChanged и добавляется запись в лог.
        /// </remarks>
        public async Task DeleteCarAsync(Guid id)
        {
            Car? carToRemove = _cars.FirstOrDefault(c => c.Id == id);
            if (carToRemove != null)
            {
                _cars.Remove(carToRemove);
                await _logService.LogInfoAsync($"Удален автомобиль: {carToRemove.Brand}");
                CollectionChanged?.Invoke(this, EventArgs.Empty);
            }
            else
            {
                throw new KeyNotFoundException($"Автомобиль с ID {id} не найден");
            }
        }

        /// <summary>
        /// Ищет автомобили, удовлетворяющие условию, заданному лямбда-выражением.
        /// </summary>
        /// <param name="predicate">Лямбда-выражение, возвращающее true, если автомобиль удовлетворяет условию.</param>
        /// <returns>Список автомобилей, удовлетворяющих условию.</returns>
        public async Task<IEnumerable<Car>> SearchCarsAsync(Expression<Func<Car, bool>> predicate)
        {
            var compiledPredicate = predicate.Compile();
            return await Task.FromResult(_cars.Where(compiledPredicate).ToList());
        }

        /// <summary>
        /// Сортирует автомобили по указанному полю.
        /// </summary>
        /// <typeparam name="TKey">Тип поля, по которому производится сортировка.</typeparam>
        /// <param name="keySelector">Лямбда-выражение, возвращающее поле, по которому производится сортировка.</param>
        /// <param name="ascending">true, если сортировка по возрастанию, false - если по убыванию.</param>
        /// <returns>Отсортированный список автомобилей.</returns>
        public async Task<IEnumerable<Car>> SortCarsAsync<TKey>(Expression<Func<Car, TKey>> keySelector, bool ascending = true)
        {
            var compiledSelector = keySelector.Compile();
            return await Task.FromResult(
                ascending
                    ? _cars.OrderBy(compiledSelector).ToList()
                    : _cars.OrderByDescending(compiledSelector).ToList()
            );
        }

        /// <summary>
        /// Сохраняет данные в файл JSON.
        /// </summary>
        /// <remarks>
        /// Если файл существует, он будет перезаписан.
        /// </remarks>
        public async Task SaveDataAsync()
        {
            try
            {
                var options = new JsonSerializerOptions { WriteIndented = true };
                string json = JsonSerializer.Serialize(_cars, options);
                await File.WriteAllTextAsync(_dataFilePath, json);
                await _logService.LogInfoAsync("Данные сохранены успешно");
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при сохранении данных: {ex.Message}");
                throw;
            }
        }

        /// <summary>
        /// Загружает данные автомобилей из файла.
        /// </summary>
        /// <remarks>
        /// Если файл существует и содержит корректные данные, коллекция автомобилей будет обновлена,
        /// и будет вызвано событие CollectionChanged. В случае ошибки будет записано сообщение об ошибке в лог.
        /// </remarks>
        public async Task LoadDataAsync()
        {
            try
            {
                if (File.Exists(_dataFilePath))
                {
                    string json = await File.ReadAllTextAsync(_dataFilePath);
                    var options = new JsonSerializerOptions { PropertyNameCaseInsensitive = true };
                    var loadedCars = JsonSerializer.Deserialize<List<Car>>(json, options);
                    if (loadedCars != null)
                    {
                        _cars = loadedCars;
                        await _logService.LogInfoAsync("Данные загружены успешно");
                        CollectionChanged?.Invoke(this, EventArgs.Empty);
                    }
                }
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при загрузке данных: {ex.Message}");
                throw;
            }
        }

        /// <summary>
        /// Экспортирует данные в файл JSON.
        /// </summary>
        /// <param name="filePath">Путь к файлу JSON.</param>
        /// <returns>true, если экспорт выполнен успешно, false - если произошла ошибка.</returns>
        public async Task<bool> ExportToJsonAsync(string filePath)
        {
            try
            {
                var options = new JsonSerializerOptions { WriteIndented = true };
                string json = JsonSerializer.Serialize(_cars, options);
                await File.WriteAllTextAsync(filePath, json);
                await _logService.LogInfoAsync($"Данные экспортированы в JSON: {filePath}");
                return true;
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при экспорте в JSON: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Импортирует данные из файла JSON.
        /// </summary>
        /// <param name="filePath">Путь к файлу JSON.</param>
        /// <returns>true, если импорт выполнен успешно, false - если произошла ошибка.</returns>
        public async Task<bool> ImportFromJsonAsync(string filePath)
        {
            try
            {
                if (File.Exists(filePath))
                {
                    string json = await File.ReadAllTextAsync(filePath);
                    var options = new JsonSerializerOptions { PropertyNameCaseInsensitive = true };
                    var importedCars = JsonSerializer.Deserialize<List<Car>>(json, options);
                    if (importedCars != null)
                    {
                        _cars = importedCars;
                        await _logService.LogInfoAsync($"Данные импортированы из JSON: {filePath}");
                        CollectionChanged?.Invoke(this, EventArgs.Empty);
                        return true;
                    }
                }
                return false;
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при импорте из JSON: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Экспортирует данные в файл XML.
        /// </summary>
        /// <param name="filePath">Путь к файлу XML.</param>
        /// <returns>true, если экспорт выполнен успешно, false - если произошла ошибка.</returns>
        public async Task<bool> ExportToXmlAsync(string filePath)
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Car>));
                using (StreamWriter writer = new StreamWriter(filePath))
                {
                    serializer.Serialize(writer, _cars);
                }
                await _logService.LogInfoAsync($"Данные экспортированы в XML: {filePath}");
                return true;
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при экспорте в XML: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Импортирует автомобили из файла XML.
        /// </summary>
        /// <param name="filePath">Путь к файлу XML.</param>
        /// <returns>true, если импорт выполнен успешно, false - если произошла ошибка.</returns>
        public async Task<bool> ImportFromXmlAsync(string filePath)
        {
            try
            {
                if (File.Exists(filePath))
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(List<Car>));
                    using (StreamReader reader = new StreamReader(filePath))
                    {
                        var importedCars = (List<Car>)serializer.Deserialize(reader);
                        if (importedCars != null)
                        {
                            _cars = importedCars;
                            await _logService.LogInfoAsync($"Данные импортированы из XML: {filePath}");
                            CollectionChanged?.Invoke(this, EventArgs.Empty);
                            return true;
                        }
                    }
                }
                return false;
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при импорте из XML: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Генерация отчета о коллекции автомобилей.
        /// </summary>
        /// <returns>Отчет в виде строки.</returns>
        /// <remarks>
        /// Отчет содержит общую статистику (количество автомобилей, общая стоимость, средняя мощность, средний год выпуска),
        /// статистику по типам автомобилей и список всех автомобилей с подробной информацией.
        /// </remarks>
        public async Task<string> GenerateReportAsync()
        {
            try
            {
                string report = "Отчет о коллекции автомобилей\n";
                report += $"Дата создания: {DateTime.Now}\n";
                report += $"Количество автомобилей: {_cars.Count}\n\n";

                // Общая статистика
                decimal totalCost = _cars.Sum(c => c.Cost);
                double avgPower = _cars.Average(c => c.Power);
                int avgYear = (int)_cars.Average(c => c.YearOfManufacture);

                report += "Общая статистика:\n";
                report += $"Общая стоимость: {totalCost:C}\n";
                report += $"Средняя мощность: {avgPower:F1} л.с.\n";
                report += $"Средний год выпуска: {avgYear}\n\n";

                // Статистика по типам
                report += "Статистика по типам автомобилей:\n";
                var typeGroups = _cars.GroupBy(c => c.CarType);
                foreach (var group in typeGroups)
                {
                    report += $"- {group.Key}: {group.Count()} шт.\n";
                }

                report += "\nСписок автомобилей:\n";
                foreach (var car in _cars)
                {
                    report += $"- {car.GetInfo()}\n";
                }

                await _logService.LogInfoAsync("Отчет сгенерирован успешно");
                return report;
            }
            catch (Exception ex)
            {
                await _logService.LogErrorAsync($"Ошибка при генерации отчета: {ex.Message}");
                return $"Ошибка при генерации отчета: {ex.Message}";
            }
        }
    }
}
