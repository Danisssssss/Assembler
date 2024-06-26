﻿#include <iostream> // подключаем библиотеку с функциями ввода-вывода (printf, system)
using namespace std; // используем пространство имен std

int main() { // обычный код на C++
    setlocale(LC_ALL, "RU"); // Подключение русского языка
    // Вывод информации о разработчике и номере варианта
    cout << "Фамилия разработчика: Яхьяев Данис" << endl;
    cout << "Номер практического занятия: Лабораторная работа №1" << endl;
    cout << "Номер варианта: №18" << endl;
    cout << "=========================" << endl;
    // Вычислить: Y = d - b - a + c
    // -- Тестовые значения-- 
    // для a = 1, b = 2, c = 3, d = 4 ожидается ответ 4
    // для a = 5, b = 7, c = 9, d = 1 ожидается ответ -2
    // для a = -4, b = 2, c = 7, d = -5 ожидается ответ 4

    int a, b, c, d; // Объявление переменных для хранения значений a, b, c и d
    cout << "Введите значения a, b, c и d: "; // Вывод сообщения на экран и ожидание ввода значений a, b, c и d
    cin >> a >> b >> c >> d;

    int result_cpp = d - b - a + c; // Вычисление выражения Y на C++ и сохранение результата в переменной result_cpp

    cout << "Результат вычисления на C++: Y = " << d << " - " << b << " - " << a << " + " << c << " = " << result_cpp << endl; // Вывод результата вычисления на C++ на экран

    // Вставка ассемблерного кода для вычисления Y
    int result_asm;
    __asm {
        mov eax, d; // Загрузка значение перменной d в регистр eax
        sub eax, b; // Вычитание b из eax
        sub eax, a; // Вычитание a из eax
        add eax, c; // Добавление c к eax
        mov result_asm, eax // Заграужаем значение eax в переменную result_asm
    }

    cout << "Результат вычисления на ассемблере: Y = " << result_asm << endl; // Вывод результата вычисления на ассемблере на экран

    return 0; // Завершение программы и возвращение нулевого значения
}