#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>

#define SEM_KEY 0x5678
#define SHM_KEY 0x1234
#define BUFFER_SIZE 4096

// Union для работы с семафорами
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Структура для разделяемой памяти
typedef struct
{
    char data[BUFFER_SIZE];
    int done; // Флаг завершения
} shared_data_t;

// Глобальные переменные
shared_data_t *shm_ptr = NULL;
int shmid = -1;
int semid = -1;
int sem_empty, sem_full; // Индексы семафоров

// Функция очистки ресурсов
void cleanup()
{
    if (shm_ptr)
    {
        shmdt(shm_ptr);
    }
    if (shmid != -1)
    {
        shmctl(shmid, IPC_RMID, NULL);
    }
    if (semid != -1)
    {
        semctl(semid, 0, IPC_RMID);
    }
}

// Функция для вывода дерева с красивым форматированием
void print_tree_line(int level, const char *name, char type)
{
    // Рисуем отступы и символы дерева
    for (int i = 0; i < level; i++)
    {
        if (i == level - 1)
        {
            printf("├── ");
        }
        else
        {
            printf("│   ");
        }
    }
    if (type == 'D')
    {
        // Директории синим цветом
        printf("\033[1;34m%s/\033[0m\n", name);
    }
    else
    {
        // Файлы обычным цветом
        printf("%s\n", name);
    }
}

int main()
{
    printf("Tree Server Started (Semaphores)\n");
    // Создание разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    // Подключение к разделяемой памяти
    shm_ptr = (shared_data_t *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1)
    {
        perror("shmat");
        cleanup();
        exit(1);
    }
    // Создание семафоров
    semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget");
        cleanup();
        exit(1);
    }
    // Инициализация семафоров
    union semun arg;
    // Семафор для пустого буфера
    sem_empty = 0;
    // Семафор для полного буфера
    sem_full = 1;
    // Буфер пуст, можно писать
    arg.val = 1;
    if (semctl(semid, sem_empty, SETVAL, arg) == -1)
    {
        perror("semctl SETVAL sem_empty");
        cleanup();
        exit(1);
    }
    // Буфер пуст, нельзя читать
    arg.val = 0;
    if (semctl(semid, sem_full, SETVAL, arg) == -1)
    {
        perror("semctl SETVAL sem_full");
        cleanup();
        exit(1);
    }
    printf("Semaphores created with ID: %d\n", semid);
    printf("Shared memory created with ID: %d\n", shmid);
    printf("Server PID: %d\n\n", getpid());
    printf("Waiting for client data...\n\n");
    printf("Directory Tree:\n");
    printf("###################################\n");
    // Ожидание и обработка данных от клиента
    char leftover[BUFFER_SIZE] = "";
    struct sembuf sop;
    while (!shm_ptr->done)
    {
        // Ожидаем, пока буфер не будет заполнен
        sop.sem_num = sem_full;
        // Уменьшаем семафор (ждет, если 0)
        sop.sem_op = -1;
        sop.sem_flg = 0;
        if (semop(semid, &sop, 1) == -1)
        {
            perror("semop wait full");
            break;
        }
        // Обрабатываем данные
        char combined[BUFFER_SIZE * 2];
        snprintf(combined, sizeof(combined), "%s%s", leftover, shm_ptr->data);
        // Обрабатываем построчно
        char *line = strtok(combined, "\n");
        char *last_line = NULL;
        while (line != NULL)
        {
            last_line = line;
            // Парсим строку: тип:уровень:имя
            char type;
            int level;
            char name[512];
            if (sscanf(line, "%c:%d:%511[^\n]", &type, &level, name) == 3)
            {
                print_tree_line(level, name, type);
            }
            line = strtok(NULL, "\n");
        }
        // Сохраняем неполную строку для следующей итерации
        if (last_line != NULL && combined[strlen(combined) - 1] != '\n')
        {
            strcpy(leftover, last_line);
        }
        else
        {
            leftover[0] = '\0';
        }
        // Освобождаем буфер
        sop.sem_num = sem_empty;
        // Увеличиваем семафор (буфер пуст)
        sop.sem_op = 1;
        sop.sem_flg = 0;
        if (semop(semid, &sop, 1) == -1)
        {
            perror("semop signal empty");
            break;
        }
    }
    printf("###################################\n");
    printf("\nTree display completed!\n");
    // Очистка ресурсов
    cleanup();
    printf("Server shutting down...\n");
    return 0;
}