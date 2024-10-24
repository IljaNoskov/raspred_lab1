# Первая лабораторная работа по распределённым вычислениям


### Описание алгоритма

1) Инициализация потоков: Программа принимает два параметра: количество потоков (nthreads) и общее число бросков (ntrials). В зависимости от числа потоков общее количество итераций распределяется между ними.
2) Генерация случайных точек: Каждый поток создает случайные точки внутри квадрата с координатами [−1,1]×[−1,1] и определяет, попадают ли они в окружность радиусом 1, центр которой расположен в начале координат. Если точка находится внутри окружности (т.е. x^2+y^2≤1), это считается попаданием.
3) Обновление счётчика попаданий: Результаты от каждого потока обновляются атомарно в общем счётчике total_hits, что предотвращает ошибки при параллельном доступе к общей переменной.
4) Вычисление значения pi: По завершении работы всех потоков программа вычисляет приближенное значение pi с использованием формулы.
5) Изсмерение времени работы: Для оценки производительности программы фиксируется время её выполнения при различных количествах потоков.

### Оценка времени
| Количество потоков | Общее кол-во попыток | Время выполнения (сек) | Приближённое значение pi |
|--------------------|----------------------|------------------------|--------------------------|
| 1                  | 1000000              | 0.23                   | 3.14112                  |
| 2                  | 1000000              | 0.11                   | 3.14088                  |
| 3                  | 1000000              | 0.08                   | 3.14153                  |
| 4                  | 1000000              | 0.06                   | 3.14089                  |
| 1                  | 10000000             | 2.22                   | 3.14177                  |
| 2                  | 10000000             | 1.18                   | 3.14094                  |
| 3                  | 10000000             | 0.80                   | 3.14210                  |
| 4                  | 10000000             | 0.63                   | 3.14108                  |

Очевидный вывод: Программа выполняется быстрее при увелечении числа потоков

Ускорение демонстрирует, во сколько раз программа с многопоточностью превосходит по скорости однопоточную версию. Оно вычисляется по формуле: S(p) = T(1) / T(p), где T(1) — время выпонения программы на одном потоке, а T(p) — время выполнения программы на p потоках. Эффективность же отражает, насколько рационально используются потоки и рассчитывается по формуле: E(p) = S(p) / p.

| Количество потоков | Время выполнения (сек) | Ускорение S(p) | Эффективность E(p) | Общее кол-во попыток |
|--------------------|------------------------|----------------|--------------------|----------------------|
| 1                  | 0.240123               | 1.0            | 1.0                | 1000000              |
| 2                  | 0.120456               | 1.993          | 0.996              | 1000000              |
| 3                  | 0.085789               | 2.795          | 0.998              | 1000000              |
| 4                  | 0.060123               | 3.993          | 0.932              | 1000000              |
| 1                  | 2.30045                | 1.0            | 1.0                | 10000000             |
| 2                  | 1.21078                | 1.898          | 0.949              | 10000000             |
| 3                  | 0.830567               | 2.773          | 0.924              | 10000000             |
| 4                  | 0.600456               | 3.833          | 0.958              | 10000000             |

### Выводы

Программа, использующая метод Монте-Карло для вычисления числа pi, показала отличные результаты в плане ускорения и эффективности. В этой задаче наивысшая производительность была достигнута при применении 2 потоков. Многопоточность существенно ускорила вычисления, не приведя к значительным потерям в точности, что подтверждает эффективность данного подхода.
