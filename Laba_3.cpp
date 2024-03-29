﻿#include <iostream>
#include <conio.h>
#include <math.h>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU"); // Подключение русского языка

	// Вывод информации о разработчике и номере варианта
	cout << "Фамилия разработчика: Яхьяев Данис" << endl;
	cout << "Номер практического занятия: Лабораторная работа №5-6" << endl;
	cout << "Номер варианта: №18 Вычислить (a*c - a*b) / (b^2 - c^2) + (b^2 + a*b) / (3*a^2 - 3*a*b)" << endl;
	cout << "=========================" << endl;
	// Вычислить(a * c - a * b) / (b ^ 2 - c ^ 2) + (b ^ 2 + a * b) / (3 * a ^ 2 - 3 * a * b)
	// -- Тестовые значения-- 
	// для a = 2, b = 4, c = 3 ожидается ответ -2.28571
	// для a = 3, b = 5, c = 4 ожидается ответ -2.55556
	// для a = 5, b = 15, c = 25 ожидается ответ -2.125
	// для a = 2, b = 5, c = 1.5 ожидается ответ -2.25214
	// для a = -4, b = -5.2, c = -2.5 ожидается ответ -3.8417

	double a, b, c;

	cout << "Введите a: "; cin >> a; // ввод числа х по шаблону 00.00
	cout << "Введите b: "; cin >> b; // ввод числа y по шаблону 00.00
	cout << "Введите c: "; cin >> c; // ввод числа y по шаблону 00.00

	double a2, c2, b2,
		znam1 = 0, // переменная для хранения знаменателя первой дроби
		znam2 = 0, // переменная для хранения знаменателя второй дроби
		chisl1 = 0, // переменная для хранения числителя первой дроби
		chisl2 = 0, // переменная для хранения числителя второй дроби
		drob1 = 0, // переменная для хранения первой дроби
		drob2 = 0, // переменная для хранения второй дроби
		three = 3,
		resultA = 0, // результат вычисления выражения на Ассемблере
		resultC = 0, // результат вычисления выражения на C++
		ac, // переменная для хранения a*c
		ab; // переменная для хранения a*b

	__asm {
		fld a // скопировать a в st(0) (загрузить a в st(0))
		fmul c // умножить содержимое st(0) на c
		fstp ac // перенести (выгрузить) из регистра st(0) в ac

		// в результате в ячейке ac находится произведение a и c, а стек пуст
		fld a // скопировать a в st(0) (загрузить a в st(0))
		fmul b // умножить содержимое st(0) на b
		fstp ab // перенести (выгрузить) из регистра st(0) в ab

		// в результате в ячейке ab находится произведение a и b, а стек пуст
		fld a // скопировать a в st(0) (загрузить a в st(0))
		fmul a // умножить содержимое st(0) на a, получено a^2
		fmul three // после произведения получили 3a^2
		fstp a2 // скопировать 3a^2 в a2

		// в результате в ячейке a2 находится произведение 3*a*a, а стек пуст
		fld b // скопировать b в st(0)
		fmul b // умножить содержимое st(0) на b
		fstp b2 // скопировать b^2 в b2

		// в результате в ячейке b2 находится произведение b и b, а стек пуст
		fld c // скопировать c в st(0)
		fmul c // умножить содержимое st(0) на c
		fstp c2 // скопировать c^2 в c2

		// в результате в ячейке c2 находится произведение c и c, а стек пуст
		fld b2 // скопировать b2 в st(0)
		fsub c2 // b^2 - c^2
		fstp znam1 // скопировать b2 - c2 в znam1

		fld ac // скопировать ac в st(0) (загрузить ac в st(0)
		fsub ab // ac - ab
		fstp chisl1 // скопировать st(0) в chisl1

		// в результате в ячейке znam1 находится вычитание b^2 - c^2, а стек пуст
		fld chisl1 // скопировать ac в st(0) (загрузить chisl1 в st(0)
		fdiv znam1 // (ac - ab)/(b^2 - c^2)
		fstp drob1 // скопировать st(0) в drob1

		// в результате в ячейке drob1 находится деление (ac - ab)/(b^2 - c^2), а стек пуст
		fld ab // скопировать ab в st(0)
		fmul three // после произведения получили 3ab
		fstp ab // скопировать st(0) в ab

		// в результате в ячейке ab находится произведение 3*a*b, а стек пуст
		fld a2 // скопировать a2 в st(0)
		fsub ab // 3a^2 - 3a*b
		fstp znam2 // скопировать st(0) в znam2

		// в результате в chisl1 находится a*c - a*b, а стек пуст
		fld b // скопировать b в st(0)
		fld b // скопировать b в st(0)
		fmul // умножить b на b, результат будет в st(0)
		fld a // скопировать a в st(0)
		fld b // скопировать b в st(0)
		fmul // умножить a на b, результат будет в st(0)
		fadd // сложить b^2 и ab, результат будет в st(0)
		fst chisl2 // скопировать st(0) в chisl2

		// в результате в ячейке znam2 находится вычитание 3a^2 - 3a*b, а стек пуст
		fdiv znam2 // (b^2 + ab)/(3a^2 - 3a*b)
		fstp drob2 // скопировать st(0) в drob2

		// в результате в ячейке drob2 находится деление (b^2 + ab)/(3a^2 - 3a*b), а стек пуст
		fld drob1 // скопировать drob1 в st(0)
		fadd drob2 // (ac - ab)/(b^2 - c^2) + (b^2 + ab)/(3a^2 - 3a*b)
		fstp resultA // скопировать st(0) в resultA
	}

	cout << "Результат (на языке Assembler): " << resultA << endl;
	cout << "Проверка на Assembler:" << endl;
	cout << "Числитель первой дроби chisl1 = " << chisl1 << endl;
	cout << "Знаменатель первой дроби zn1 = " << znam1 << endl;
	cout << "Числитель второй дроби chisl2 = " << chisl2 << endl;
	cout << "Знаменатель второй дроби zn2 = " << znam2 << endl;
	cout << "Числитель второй дроби drob1 = " << drob1 << endl;
	cout << "Знаменатель второй дроби drob2 = " << drob2 << endl;

	// -- вычисление формулы на С++ --
	resultC = (a * c - a * b) / (b * b - c * c) + (b * b + a * b) / (3 * a * a - 3 * a * b);
	cout << "Результат (на языке C++): " << resultC << endl;
	chisl1 = a * c - a * b;
	chisl2 = b * b + a * b;
	znam1 = b * b - c * c;
	znam2 = 3 * a * a - 3 * a * b;
	drob1 = chisl1 / znam1;
	drob2 = chisl2 / znam2;
	cout << "Проверка на C++:" << endl;
	cout << "Числитель первой дроби chisl1 = " << chisl1 << endl;
	cout << "Знаменатель первой дроби zn1 = " << znam1 << endl;
	cout << "Числитель второй дроби chisl2 = " << chisl2 << endl;
	cout << "Знаменатель второй дроби zn2 = " << znam2 << endl;
	cout << "Числитель второй дроби drob1 = " << drob1 << endl;
	cout << "Знаменатель второй дроби drob2 = " << drob2 << endl;
	cout << "(" << a << "*" << c << "-" << a << "*" << b << ")/(" << b << "^2-" << c << "^2) + (" << b << "^2+" << a << "*" << b
		<< ")/( 3*" << a << "^2-3" << "*" << a << "*" << b << ")=" << resultC << endl;

	if (fabs(resultA - resultC) < 0.00001) { // Если |resultA - resultC| < 0.00001
		cout << "Разработанная программа на Ассемблере работает правильно! " << endl;
	}
	else {
		cout << "ПРОГРАММА НЕПРАВИЛЬНАЯ!!! " << endl;
	}

	system("pause");
	return 0;
}