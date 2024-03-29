#include <iostream>
#include <conio.h>
#include <math.h>
#include <cmath> // подключаем библиотеку математических функций

using namespace std;

int zadanie_1() {
    // Задание № 1:
    // y = a + bx, если х > 0;
    // y = x^2, если х < 0:
    // y = 1, если х = 0;
    // -- Тестовые значения --
    // a = 6, b = 8
    // для x = 2, ожидается ответ 22
    // для x = -13, ожидается ответ 169
    // для x = 0, ожидается ответ 1
    int a = 6,
        b = 8,
        x,
        y; // объявляем переменные и инициализируем a и b
    cout << "Введите x: ";
    cin >> x;	// ввод значения x

    __asm
    {
        mov eax, x // поместили x в регистр eax
        cmp eax, 0 // сравнили: x == 0
        je equ // если x = 0 переходим на метку equ
        jg abov // если x > 0 переходим на метку abo
        imul x // если x < 0 eax *= x
        jmp finish // переход на метку finish
        equ :
        mov eax, 1 // x = 0; ebx = a
            jmp finish // переход на метку finish  
            abov :
        imul b // x > 0; eax *= b
            add eax, a // eax += a (eax = a + bx)
            finish : mov y, eax // поместили результат в y
    }
    cout << "Яхьяев Данис. Лабораторная работа № 07-08. Вариант №18.\n"
        << "Результаты вычислений на Assembler: " << y << endl;

    // -- Формулы на С++ --
    if (x == 0) {
        y = 1;
    }
    else if (x > 0) {
        y = a + b * x;
    }
    else {
        y = x * x;
    }

    cout << "Результаты вычислений на C++: " << y << endl << endl;
    system("pause");
    return 0;
}

int zadanie_2() {
    // Задание № 2:
    // Ввести целое число. если оно является положительным, то прибавить к нему 1; 
    // в противном случае не изменять его. вывести полученное число
    // -- Тестовые значения --
    // x = 7, ожидается 8
    // x = -5, ожидается -5

    int x, resa, resc; // объявляем переменные

    cout << "Введите x: ";
    cin >> x; // ввод значения x

    __asm
    {
        mov eax, x // поместили x в регистр eax
        cmp eax, 0 // сравнили: x == 0

        jns positive // если x > 0 переходим на метку positive
        jmp finish // если x < 0 переход на метку finish

        positive : inc eax // ++x

        finish : mov resa, eax // поместили результат в resa
    }

    cout << "Яхьяев Данис. Лабораторная работа № 07-08. Вариант №18.\n"
        << "Результаты вычислений на Аssembler: " << resa << endl;

    // -- Формулы на С++ -- 
    if (x > 0) {
        resc = ++x;
    }
    else {
        resc = x;
    }

    cout << "Результаты вычислений на С++: " << resc << endl << endl;
    system("pause");
    return 0;
}

int zadanie_3() {
    // Задание № 3:
    // Ввести три целых числа. Найти наименьшее из них.

    // -- Тестовые значения --
    // x = 4, y = 10, z = 3 ожидается 3
    // x = 122, y = 52, z = 332 ожидается 52
    // x = -132, y = -234, z = -13 ожидается -234

    int x, y, z, resa, resc; // объявляем переменные

    cout << "Введите x: ";
    cin >> x; // ввод значения x
    cout << "Введите y: ";
    cin >> y; // ввод значения y
    cout << "Введите z: ";
    cin >> z; // ввод значения z

    __asm
    {
        mov eax, x // поместили x в регистр eax

        cmp eax, y // сравнили: x == y
        jle XlessY // если x <= y, то переход на метку XlessY

        mov eax, y // если y < x, то копируем в регистр eax значение y

        cmp eax, z // сравнили y == z
        jg Z_isSmall // если z < y, то переход на метку Z_isSmall
        jmp finish // если y <= z, то переход на метку finish

        XlessY : cmp eax, z // сравнили x == z
        jg Z_isSmall // если z < x, то переход на метку Z_isSmall
        jmp finish // если x <= z, то переход на метку finish

        Z_isSmall : mov eax, z // поместили значение z в регистр eax

        finish : mov resa, eax // поместили результат в resa
    }

    cout << "Яхьяев Данис. Лабораторная работа № 07-08. Вариант №18.\n"
        << "Результаты вычислений на Assembler: " << resa << endl;

    // -- Формулы на С++ -- 
    if (x <= y) {
        if (x <= z) {
            resc = x;
        }
        else {
            resc = z;
        }
    }
    else {
        if (y <= z) {
            resc = y;
        }
        else {
            resc = z;
        }
    }

    cout << "Результаты вычислений на C++: " << resc << endl << endl;
    system("pause");
    return 0;
}

int zadanie_4() {
    // Задание № 4:
    // Ввести три целых числа. Найти количество положительных чисел в исходном наборе.

    // -- Тестовые значения --
    // x = 1, y = 2, z = 3 ожидается 3
    // x = -1, y = 2, z = -3 ожидается 1
    // x = -1, y = -2, z = -3 ожидается 0

    int x, y, z, resa = 0, resc = 0; // объявляем переменные

    cout << "Введите x: ";
    cin >> x; // ввод значения x
    cout << "Введите y: ";
    cin >> y; // ввод значения y
    cout << "Введите z: ";
    cin >> z; // ввод значения z

    __asm
    {
        mov eax, x // поместили x в регистр eax
        cmp eax, 0 // сравнили: x == 0
        jns posX // если x < 0, то переход на метку negX
        jmp analyseY // если x > 0, то переход на метку analyseY
        posX : inc resa // ++resa

        analyseY :
        mov eax, y // поместили y в регистр eax
            cmp eax, 0 // сравнили: y == 0
            jns posY // если y < 0, то переход на метку negY
            jmp analyseZ // если x > 0, то переход на метку analyseZ
            posY : inc resa // ++resa

            analyseZ :
        mov eax, z // поместили z в регистр eax
            cmp eax, 0 // сравнили: z == 0
            jns posZ // если z < 0, то переход на метку negZ
            jmp finish // если x > 0, то переход на метку analyseZ
            posZ : inc resa // ++resa

            finish :
    }

    cout << "Яхьяев Данис. Лабораторная работа № 07-08. Вариант №18.\n"
        << "Результаты вычислений на Assembler: " << resa << endl;

    // -- здесь вычисление формулы на С++ -- 
    if (x > 0) {
        ++resc;
    }
    if (y > 0) {
        ++resc;
    }
    if (z > 0) {
        ++resc;
    }

    cout << "Результаты вычислений на C++: " << resc << endl << endl;
    system("pause");
    return 0;
}

int zadanie_5() {
    // Задание № 5:
    // На числовой оси расположены три точки: A, B, C. Определить, какая из двух последних точек (B или C) 
    // расположена ближе к A, вывести эту точку и ее расстояние от точки A.

    // -- Тестовые значения --
    // A = 1, B = -4, C = 4 ожидается B 4
    // A = -4, B = -8, C = 0 ожидается B -8 или C 0


    int A, B, C, resa = 0, resc = 0; // объявляем переменные
    char b = 'B', c = 'C', ansa, ansc; // объявляем переменные

    cout << "Введите A: ";
    cin >> A; // ввод значения A
    cout << "Введите B: ";
    cin >> B; // ввод значения B
    cout << "Введите C: ";
    cin >> C; // ввод значения C

    __asm
    {
        mov eax, A // поместили A в регистр eax
        mov ebx, A // поместили A в регистр ebx

        sbb eax, B // нашли расстояние от A до В
        sbb ebx, C // нашли расстояние от А до С

        moduleAB : neg eax // поменяли знак eax, чтобы его найти модуль
        js moduleAB // если eax отрицательный, то меняем ещё раз

        moduleAC : neg ebx // поменяли знак ebx, чтобы его найти модуль
        js moduleAC // если ebx отрицательный, то меняем ещё раз

        cmp eax, ebx // сравниваем расстояния до В и до С
        jg C_closer // если C ближе, то переход на метку C_closer
        mov eax, B // если B ближе, то сбрасываем значение регистра на значение B
        mov ansa, 'B' // поместили в ansa букву B
        jmp finish // переход на метку finish

        C_closer : mov eax, C // заменили значение eax на C
        mov ansa, 'C' // поместили в ansa букву С

        finish : mov resa, eax // записали ответ в resa
    }

    cout << "Яхьяев Данис. Лабораторная работа № 07-08. Вариант №18.\n";
    printf_s("Результаты вычислений на Assembler: %c %d\n", ansa, resa);

    // -- здесь вычисление формулы на С++ -- 
    if (abs(A - B) < abs(A - C)) { // используем функцию вычисления модуля для упрощения
        ansc = 'B';
        resc = B;
    }
    else {
        ansc = 'C';
        resc = C;
    }

    printf_s("Результаты вычислений на C++: %c %d\n\n", ansc, resc);
    system("pause");
    return 0;
}

int main() {
    setlocale(LC_ALL, "RU");
    // zadanie_1();
    // zadanie_2();
    // zadanie_3();
    // zadanie_4();
    zadanie_5();

    system("pause");
    return 0;
}