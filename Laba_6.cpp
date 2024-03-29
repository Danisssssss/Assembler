#include <iostream>
#include <cmath>

using namespace std;

void FullBranch(double x, double y)
{
	const double ten = 10, two = 2, three = 3, sfive = -5, one_third = 1.0 / 3.0; // объявляем и инициализируем константные переменные

	__asm
	{
		fld sfive // скопировали -5 в st(0)
		fld x // скопировали x в st(0), а -5 провалилось в st(1)
		fcomi st, st(1) // сравниваем x с -5

		jb X_Less_s3 // если x < -5, то переходим на метку X_Less_s3
		jge X_Greater_s3 // если x >= -5, то переходим на метку X_Greater_s3

		X_Less_s3 :
		fld two // st(0) = 2
			fld x // st(0) = x, st(1) = 2
			fdiv // st(0) = 2/x
			jmp finish // переход к финишу

			X_Greater_s3 : // x > -5
		fld two // st(0) = 2, st(1) = x
			fxch // st(0) = x, st(1) = 4 (st(0) <-> st(1))
			fcomi st, st(1)	// сравниваем x c 2
			jb X_Less_4 // если x < 2, то переходим на метку X_Less_4
			jge X_Greater_4 // если x >= 2, то переходим на метку X_Greater_4

			X_Less_4 : // x < 2
		fsin // st(0) = sin(x)
			fld x // st(0) = x, st(1) = sin(x)
			fmul // st(0) = x * sin(x)
			jmp finish // переход к финишу

			X_Greater_4 :// x > 2
		fld three // st(0) = 3, st(1) = x
			fxch // st(0) <-> st(1)
			fcomi st, st(1)	// сравниваем x c 3
			jae X_Greater_6	// если x >= 3, то переходим на метку X_Greater_6
			// если x < 3, то продолжаем
			fadd ten // st(0) = x + 10
			fld x // st(0) = x, st(1) = x + 10
			fmul x // st(0) = x^2
			fadd two // st(0) = x^2 + 2
			fdivp st(1), st // (x+10)/(x^2+2)
			jmp finish // переход к финишу

			X_Greater_6 : // x > 3
		fld one_third // st(0) = 1.0/3.0
			fld x // st(0) = x, st(1) = 1.0/3.0 
			fyl2x // st(0) = log2(x) * 1.0/3.0
			fld st // st(0) = log2(x) * 1.0/3.0, st(1) = log2(x) * 1.0/3.0
			frndint // Округление log2(x)*1.0/3.0 к ближайшему целому, результат в st(0), целое число в st(1)
			fxch // st(0) <-> st(1)
			fsub st, st(1) // st(0) = st(0) - st(1)
			f2xm1 // x(0) = 2^x - 1, где x - дробная часть log2(x)
			fld1 // x(0) = 1, x(1) = 2^x - 1
			fadd // x(0) = 1 + 2^x - 1
			fscale // умножение
			fld x // st(0) = x, st(1) = 2^x
			fadd  // x + 2^x
			jmp finish // переход к финишу


			finish : fstp y // поместили результат в y
	}

	cout << "Результаты вычислений на Assembler: " << y << endl;

	// -- здесь вычисление формулы на С++ -- 
	if (x < -5) y = 2 / x;
	else if (x >= -5 && x < 2) y = x * sin(x);
	else if (x >= 2 && x < 3) y = (x + 10) / (2 + x * x);
	else if (x >= 3) y = x + pow(x, 1.0 / 3);
	cout << "Результаты вычислений на C++: " << y << endl << endl;
}

void UnfullBranch(double x, double y)
{
	const double ten = 10, two = 2, three = 3, sfive = -5, one_third = 1.0 / 3.0; // объявляем и инициализируем константные переменные

	__asm
	{
		fld sfive // скопировали -5 в st(0)
		fld x // скопировали x в st(0), а -5 провалилось в st(1)
		fcomi st, st(1)	// сравниваем x с -5

		jb X_Less_s3 // если x < -5, то переходим на метку X_Less_s3

		fld two // st(0) = 2, st(1) = x
		fxch // st(0) = x, st(1) = 2 (st(0) <-> st(1))
		fcomi st, st(1) // сравниваем x c 2
		jb X_Less_4 // если x < 2, то переходим на метку X_Less_4

		fld three // st(0) = 3, st(1) = x
		fxch // st(0) <-> st(1)
		fcomi st, st(1) // сравниваем x c 3
		jae X_Greater_6 // если x >= 3, то переходим на метку X_Greater_6
		// если x < 3, то продолжаем

		fadd ten // st(0) = x + 10
		fld x // st(0) = x, st(1) = x + 10
		fmul x // st(0) = x^2
		fadd two // st(0) = x^2 + 2
		fdivp st(1), st // (x+10)/(x^2+2)
		jmp finish // переход к финишу

		X_Greater_6 : // x > 3

		fld one_third // st(0) = 1.0/3.0
			fld x // st(0) = x, st(1) = 1.0/3.0 
			fyl2x // st(0) = log2(x) * 1.0/3.0
			fld st // st(0) = log2(x) * 1.0/3.0, st(1) = log2(x) * 1.0/3.0
			frndint // Округление log2(x)*1.0/3.0 к ближайшему целому, результат в st(0), целое число в st(1)
			fxch // st(0) <-> st(1)
			fsub st, st(1) // st(0) = st(0) - st(1)
			f2xm1 // x(0) = 2^x - 1, где x - дробная часть log2(x)
			fld1 // x(0) = 1, x(1) = 2^x - 1
			fadd // x(0) = 1 + 2^x - 1
			fscale // умножение
			fld x // st(0) = x, st(1) = 2^x
			fadd  // x + 2^x
			jmp finish // переход к финишу

			X_Less_4 : // x < 2 
		fsin // st(0) = sin(x)
			fld x // st(0) = x, st(1) = sin(x)
			fmul // st(0) = x * sin(x)
			jmp finish // переход к финишу

			X_Less_s3 : // x < -5
		fld two // st(0) = 2
			fld x // st(0) = x, st(1) = 2
			fdiv // st(0) = 2/x

			finish : fstp y // поместили результат в y
	}

	cout << "Результаты вычислений на Assembler: " << y << endl;

	// -- здесь вычисление формулы на С++ -- 
	if (x < -5) y = 2 / x;
	if (x >= -5 && x < 2) y = x * sin(x);
	if (x >= 2 && x < 3) y = (x + 10) / (2 + x * x);
	if (x >= 3) y = x + pow(x, 1.0 / 3);

	cout << "Результаты вычислений на C++: " << y << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian"); // установка русского алфавита
	// если x < -5, то y = 2/x
	// если -5 <= x < 2, то y = x * sin(x)
	// если 2 <= x < 3, то y = (x + 10) / (2 + x * x)
	// если x >= 3, то y = x + x^(1/3)

	// -- тестовые значения --
	// для х = -10, ожидается ответ -0.2
	// для х = -6, ожидается ответ -0.333333
	// для х = -5, ожидается ответ -4.79462
	// для х = 0, ожидается ответ 0
	// для х = 1, ожидается ответ 0.841471
	// для х = 2, ожидается ответ 2
	// для х = 4, ожидается ответ 5.5874
	// для х = 8, ожидается ответ 10

	int choice; // объявляем переменную выбора решения
	double x = 0, y = 0; // объявляем переменные и инициализируем в ноль

	cout << "Яхьяев Данис. Лабораторная работа № 11-12. Вариант №18(3)." << endl;

	cout << "Введите способ решения:" << endl << "1.Полное ветвление" <<
		endl << "2.Краткая форма ветвления" << endl << endl << "Ввод: ";
	cin >> choice;

	if (cin.good()) {
		cout << "Введите x: ";
		cin >> x;	//ввод значения x
	}

	switch (choice)
	{
	case 1:
		FullBranch(x, y);
		break;
	case 2:
		UnfullBranch(x, y);
		break;
	default:
		break;
	}
	return 0;
}