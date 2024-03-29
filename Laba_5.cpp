#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");

	cout << "Фамилия разработчика: Яхьяев Данис" << endl;
	cout << "Номер практического занятия: Лабораторная работа №9-10" << endl;
	cout << "Номер варианта: №18" << endl;
	cout << "=========================" << endl;

	double x, y;
	const double threshold = 3;
	const double term1 = 3;
	const double term2 = 9;

	// -- тестовые значения --
	// для x = 0, ожидается ответ 9
	// для x = 1, ожидается ответ 11
	// для x = 4, ожидается ответ -0.0302721

	cout << "Введите x: ";
	cin >> x;

	__asm
	{
		fld threshold     // Загружаем порог в стек (st(0))
		fld x             // Загружаем x в стек (st(0)), порог переходит в st(1)
		fcomi st, st(1)  // Сравниваем x с порогом и убираем значения из стека

		ja X_isntLessOrEqual // Если x >= threshold, переходим на метку X_isntLessOrEqual
		// Если x < threshold, продолжаем
		fld x             // Загружаем x снова в стек (st(0) = x)
		fld x             // Загружаем x в стек (st(0) = x, st(1) = x)
		fmul            // st(0) = x * x
		fchs              // Изменяем знак, теперь st(0) = -(x^2)
		fld x             // Загружаем x снова в стек (st(0) = x, st(1) = -(x^2))
		fld term1        // Загружаем term1 в стек (st(0) = term1, st(1) = x, st(2) = -(x^2))
		fmul             // st(0) = term1 * x
		fadd term2        // st(0) = term1 * x + term2
		fadd
		jmp finish        // Переходим на метку finish


		X_isntLessOrEqual :
		fsin              // Вычисляем синус x (st(0) = sin(x))
			fld x             // Загружаем x в стек (st(0) = x, st(1) = sin(x))
			fld x             // Загружаем x в стек (st(0) = x, st(1) = x, st(2) = sin(x))
			fmul            // st(0) = x * x
			fadd term2        // st(0) = x^2 + term2
			fdiv             // Выполняем деление sin(x) / (x^2 + term2)

			finish :
		fstp y            // Результат помещаем в y
	}

	// -- Результаты вычислений на Assembler --
	cout << "Результаты вычислений на Assembler: " << y << endl;

	// -- Результаты вычислений на С++ --
	if (x <= threshold) {
		y = -(x * x) + term1 * x + term2;
	}
	else {
		y = (sin(x)) / (x * x + term2);
	}
	cout << "Результаты вычислений на C++: " << y << endl;

	system("pause");
	return 0;
}