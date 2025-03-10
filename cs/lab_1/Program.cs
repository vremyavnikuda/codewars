using System;
using System.Windows.Forms;

namespace CarManagementApp
{
    /// <summary>
    /// Класс <c>Program</c> является точкой входа для приложения CarManagementApp.
    /// </summary>
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        /// <remarks>
        /// Метод <c>Main</c> инициализирует визуальные стили, настраивает совместимость с рендерингом текста и запускает главную форму приложения.
        /// Для корректной работы приложения используется атрибут <c>[STAThread]</c>.
        /// </remarks>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}