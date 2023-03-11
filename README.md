# LW_OpenMP
Из легких задач были выполнены следующие:
- Задание 1. Написать программу где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли вывод идентичен? Почему? 
- Задание 3. Модифицируйте задачу 1 так, чтобы потоки распечатывали свои идентификаторы в обратном порядке. Существует как минимум 5 способов решения. Постарайтесь найти как можно больше. 
- Задание 4. Напишите программу перемножения больших матриц. Сравните врем выполнения последовательной и параллельной программы на 2,4, 8 потоках (процессорах) 

Основная задача:
11. Разработайте программу решения задачи определения транспонированной матрицы для квадратной матрицы. 


Task 1
Thread id: 1     Threads: 8      Hello World
Thread id: 0     Threads: 8      Hello World
Thread id: 2     Threads: 8      Hello World
Thread id: 7     Threads: 8      Hello World
Thread id: 4     Threads: 8      Hello World
Thread id: 5     Threads: 8      Hello World
Thread id: 6     Threads: 8      Hello World
Thread id: 3     Threads: 8      Hello World

Task 3
Thread id: 7     Threads: 8      Hello World
Thread id: 6     Threads: 8      Hello World
Thread id: 5     Threads: 8      Hello World
Thread id: 4     Threads: 8      Hello World
Thread id: 3     Threads: 8      Hello World
Thread id: 2     Threads: 8      Hello World
Thread id: 1     Threads: 8      Hello World
Thread id: 0     Threads: 8      Hello World

Task 4
Sequential version: 17.8697 s
Parallel version with 2 threads: 7.49499 s
Parallel version with 4 threads: 5.93416 s
Parallel version with 8 threads: 4.11677 s
