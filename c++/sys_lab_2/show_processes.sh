#!/bin/bash

echo "Активные процессы на Arch Linux:"

# Active states: R (running), S (sleeping), D (uninterruptible sleep), T (stopped), Z (zombie)
echo "Все активные процессы (состояния: R, S, D, T, Z):"
ps -eo pid,ppid,stat,comm,user,%cpu,%mem,time,args --sort=-%cpu | awk 'NR == 1 || $3 ~ /^[RSDTZ]/ {print}'
echo "Процессы с наибольшим использованием CPU:"
ps -eo pid,stat,comm,user,%cpu,%mem --sort=-%cpu | awk 'NR == 1 || (NR > 1 && $2 ~ /^[RSDTZ]/)' | head -15
echo ""
echo "Процессы с наибольшим использованием памяти:"
ps -eo pid,stat,comm,user,%cpu,%mem --sort=-%mem | awk 'NR == 1 || (NR > 1 && $2 ~ /^[RSDTZ]/)' | head -15
echo "Дерево активных процессов:"
pstree -p

echo ""
echo "Справка по состояниям процессов:"
echo "  R - Running или выполнение на CPU"
echo "  S - Sleeping (прерываемый сон)"
echo "  D - Uninterruptible sleep (обычно ввод/вывод)"
echo "  T - Stopped (например, сигналом SIGTSTP)"
echo "  Z - Zombie (мертвый, но все еще в таблице процессов)"

echo ""
echo "Загрузка системы:"
uptime
echo "Готово!"
