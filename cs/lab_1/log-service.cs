using System;
using System.IO;
using System.Threading.Tasks;

namespace CarManagementApp.Services
{
    // Интерфейс для сервиса логирования
    public interface ILogService
    {
        Task LogInfoAsync(string message);
        Task LogWarningAsync(string message);
        Task LogErrorAsync(string message);
    }

    // Реализация сервиса логирования
    public class LogService : ILogService
    {
        private readonly string _logFilePath;
        private readonly object _lockObject = new object();

        /// <summary>
        /// Инициализирует новый экземпляр <see cref="LogService"/>.
        /// </summary>
        /// <param name="logDirectory">Директория для хранения файлов логов.</param>
        /// <remarks>
        /// Формирует путь к файлу логов на текущую дату в виде <c>log_{yyyy-MM-dd}.txt</c>.
        /// Если директория не существует, она будет создана.
        /// </remarks>
        public LogService(string logDirectory)
        {
            if (!Directory.Exists(logDirectory))
                Directory.CreateDirectory(logDirectory);
            _logFilePath = Path.Combine(logDirectory, $"log_{DateTime.Now:yyyy-MM-dd}.txt");
        }

        /// <summary>
        /// Асинхронно записывает информационное сообщение в лог.
        /// </summary>
        /// <param name="message">Сообщение для записи в лог.</param>

        public async Task LogInfoAsync(string message)
        {
            await LogAsync("INFO", message);
        }

        /// <summary>
        /// Асинхронно записывает предупреждение в лог.
        /// </summary>
        /// <param name="message">Сообщение для записи в лог.</param>
        public async Task LogWarningAsync(string message)
        {
            await LogAsync("WARNING", message);
        }

        /// <summary>
        /// Асинхронно записывает ошибку в лог.
        /// </summary>
        /// <param name="message">Сообщение для записи в лог.</param>
        public async Task LogErrorAsync(string message)
        {
            await LogAsync("ERROR", message);
        }

        /// <summary>
        /// Асинхронно записывает сообщение в лог.
        /// </summary>
        /// <param name="level">Уровень логирования (INFO, WARNING, ERROR).</param>
        /// <param name="message">Сообщение для записи в лог.</param>
        /// <remarks>
        /// Добавляет метку времени, уровень логирования, само сообщение
        /// и добавляет сообщение в файл логов.
        /// </remarks>
        private async Task LogAsync(string level, string message)
        {
            string logMessage = $"{DateTime.Now:yyyy-MM-dd HH:mm:ss} [{level}] {message}";
            try
            {
                lock (_lockObject)
                {
                    using (StreamWriter writer = new StreamWriter(_logFilePath, true))
                    {
                        writer.WriteLine(logMessage);
                    }
                }
                await Task.CompletedTask;
            }
            catch
            {
                // Ошибки логирования игнорируем
                await Task.CompletedTask;
            }
        }
    }
}