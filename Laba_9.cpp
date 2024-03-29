#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

// -- №1 --

void calculate(float a, float b, float c, float three, float resa, float resc)
{
	__asm {
		fld a // скопировать a в st(0)
		fmul c // a*c
		fld a // скопировать a в st(0)
		fmul b // a*b
		fsub // a*c - a*b

		fld b // скопировать b в st(0)
		fmul b // b^2
		fld c // скопировать c в st(0)
		fmul c // c^2
		fsub // b^2 - c^2

		fdiv // (a*c - a*b) / (b^2 - c^2)

		fld b // скопировать b в st(0)
		fmul b // b^2
		fld a  // скопировать a в st(0)
		fmul b // a*b
		fadd // b^2 + a*b

		fld a // скопировать a в st(0)
		fmul a // a^2
		fmul three // 3*a^2
		fld a // скопировать a в st(0)
		fmul b // a*b
		fmul three // 3*a*b
		fsub // 3*a^2 - 3*a*b

		fdiv // (b^2 + a*b) / (3*a^2 - 3*a*b)

		fadd // (a*c - a*b) / (b^2 - c^2) + (b^2 + a*b) / (3*a^2 - 3*a*b)

		fstp resa // Сохранение результата в resa
	}

	cout << "Результаты вычислений на Assembler: " << resa << endl;

	// -- здесь вычисления на С++ -- 
	resc = (a * c - a * b) / (b * b - c * c) + (b * b + a * b) / (3 * a * a - 3 * a * b);

	cout << "Результаты вычислений на C++: " << resc << endl;
}

int main()
{

	setlocale(LC_ALL, "Russian"); // установка русского алфавита

	// Задание №1
	// (a * c - a * b) / (b ^ 2 - c ^ 2) + (b ^ 2 + a * b) / (3 * a ^ 2 - 3 * a * b)

	// -- тестовые значения --
	// для a = 5, b = 15, c = 25 ожидается ответ -2.125
	// для a = 3, b = 5, c = 4 ожидается ответ -2.55556
	// для a = 2, b = 5, c = 1.5 ожидается ответ -2.25214

	int choice = 0;
	float a, b, c, resa = 0, resc = 0, three = 3; // объявляем переменные


	cout << "Яхьяев Данис. Лабораторная работа № 17-18. Вариант №18." <<
		endl << "Введите способ передачи данных:" << endl << "1. Обычно (через С++)"
		<< endl << "2. В ассемблере" << endl << "Ввод: ";
	cin >> choice;

	cout << "Введите 3 числа: ";

	cin >> a; // ввод значения a 
	cin >> b; // ввод значения b
	cin >> c; // ввод значений c

	if (choice == 1)
		calculate(a, b, c, three, resa, resc);
	else
		__asm {
		push resc
		push resa
		push three
		push c
		push b
		push a
		call calculate
		add esp, 24
	}
	return 0;
}

// -- №2 --

//void calculate(float x, float resa, float resc)
//{
//	__asm
//	{
//		fld x
//		fld st(0)
//
//		// exp(-x)
//		fchs
//		fldl2e // st(0) = 1 / ln(2) = log2(e)
//		fmul // st(0) = x / ln(2) = x * log2(e)
//		fld st
//		frndint
//		fsub st(1), st
//		fxch st(1)
//		f2xm1
//		fld1
//		fadd
//		fscale
//		fstp st(1)
//
//		// sin(2 * x)
//		fxch st(1) // st(0) = x, st(1) = exp(-x)
//		fadd st(0), st(0) // st(0) = 2 * x, st(1) = exp(-x)
//		fsin // st(0) = sin(2 * x), st(1) = exp(-x)
//		fld st(0)
//		fmul st(0), st(0)
//		fmulp st(1), st(0)
//
//		fmulp st(1), st(0) // st(0) = sin(2 * x) * exp(-x)
//
//		fstp resa
//	}
//
//	cout << "Результаты вычислений на Assembler: " << resa << endl;
//
//	// -- здесь вычисления на С++ -- 
//	resc = pow(sin(2 * x), 3) * pow(M_E, -x);
//
//	cout << "Результаты вычислений на C++: " << resc << endl;
//}
//
//int main()
//{
//
//	setlocale(LC_ALL, "Russian"); // установка русского алфавита
//
//	// Задание №2
//	// (sin(2*x))^3 * e^(-x)
//
//	// -- тестовые значения --
//	// для x = 1 ожидается ответ 0.276582
//	// для x = 0 ожидается ответ 0
//	// для x = -1 ожидается ответ -2.04368
//
//	int choice = 0;
//	float x, resa = 0, resc = 0; // объявляем переменные
//
//	cout << "Яхьяев Данис. Лабораторная работа № 17-18. Вариант №18." <<
//		endl << "Введите способ передачи данных:" << endl << "1. Обычно (через С++)"
//		<< endl << "2. В ассемблере" << endl << "Ввод: ";
//	cin >> choice;
//
//	cout << "Введите x: ";
//	cin >> x; //ввод значения x
//
//	if (choice == 1)
//		calculate(x, resa, resc);
//	else 
//		__asm {
//		push resc
//		push resa
//		push x
//		call calculate
//		add esp, 12
//	}
//	return 0;
//}

// -- №3 --

//void catEatMouse(float x, float y, float two, float three, float resa, float resc)
//{
//	__asm
//	{
//		fld x // st(0) = x
//		fmul y // x*y
//		fmul two // 2*x*y
//		fld three // st(0) = 3
//		fdiv // 2*x*y / 3
//
//		fstp resa // Сохранение результата в resa
//	}
//
//	cout << "Результаты вычислений на Assembler: " << resa << endl;
//
//	// -- здесь вычисления на С++ --
//	resc = 2 * x * y / 3;
//
//	cout << "Результаты вычислений на C++: " << resc << endl;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian"); // установка русского алфавита
//
//	// Задание №3
//	// Полторы кошки за полтора часа съедают полторы мышки.
//	// Сколько мышек съедят X кошек за Y часов. 
//
//	// -- тестовые значения --
//	// для x = 1.5, y = 1.5 ожидается ответ 1.5
//	// для x = 3, y = 4 ожидается ответ 8
//
//	int choice = 0;
//	float x, y, two = 2, three = 3, resa = 0, resc = 0;	// объявляем переменные
//
//	cout << "Яхьяев Данис. Лабораторная работа № 17-18. Вариант №18." <<
//		endl << "Введите способ передачи данных:" << endl << "1. Обычно (через С++)"
//		<< endl << "2. В ассемблере" << endl << "Ввод: ";
//	cin >> choice;
//
//	cout << "Введите X (количество кошек) ";
//	cin >> x; // ввод количества кошек
//	cout << "Введите Y (количество часов) ";
//	cin >> y; // ввод количества часов
//
//	if (choice == 1)
//		catEatMouse(x, y, two, three, resa, resc);
//	else
//		__asm {
//		push resc
//		push resa
//		push three
//		push two
//		push y
//		push x
//		call catEatMouse
//		add esp, 24
//	}
//
//	return 0;
//}