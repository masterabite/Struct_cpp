#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//класс комплексного числа
class Complex {
public:

	//конструктор по умолчанию
	Complex() {
		r = 0;
		a = 0;
	}

	//конструктор с двумя параметрами
	Complex(double _r, double _a) {
		r = _r;
		a = _a;
	}

	~Complex() {
		printf("Вызван деструктор для объекта %p\n", this);
	}

	//функция вывода числа в консоль в тригонометрической форме
	void print_tr() {
		printf("%.3lf(cos(%.3lf) + i*sin(%.3lf))", r, a, a);
	}

	//функция вывода числа в консоль в алгебраической форме
	void print_alg() {
		printf("%.3lf + i*%.3lf", r*cos(a), r*sin(a));
	}

	//функция возведения числа в степень, возвращает новое число
	Complex pow(double p) {
		return Complex(std::pow(r, p), a * p);
	};

	//функция умножения на второе число
	Complex mult(Complex c) {
		return Complex(r * c.r, a + c.a);
	};

	//функция деления на второе число
	Complex div(Complex c) {
		return Complex(r / c.r, a - c.a);
	};

	//функция сложения на второе число
	Complex add(Complex c) {
		//для сложения нужно работать с алгебраической формой
	
		//находим алгебраические коэффициенты чисел
		double a1 = r * cos(a);
		double a2 = c.r * cos(c.a);
		double b1 = r * sin(a);
		double b2 = c.r * sin(c.a);

		//суммируем
		double a = a1 + a2;
		double b = b1 + b2;

		//определяем кожффициенты тригонометрической формы
		double c_r = sqrt(a * a + b * b);   //находим модуль результата
		double c_a = acos(a / c_r);			//находим аргумент
		
		//возвращаем результат
		return Complex(c_r, c_a);
	};

	//функция вычетания на второе число
	Complex sub(Complex c) {
		//для вычетания используем то же сложение, только нужно изменить знак коэффициентов второго числа

		//находим алгебраические коэффициенты чисел
		double a1 = r * cos(a);
		double a2 = -c.r * cos(c.a);
		double b1 = r * sin(a);
		double b2 = -c.r * sin(c.a);

		//суммируем
		double a = a1 + a2;
		double b = b1 + b2;

		//определяем кожффициенты тригонометрической формы
		double c_r = sqrt(a * a + b * b);   //находим модуль результата
		double c_a = acos(a / c_r);			//находим аргумент

		//возвращаем результат
		return Complex(c_r, c_a);
	};
private:
	double r, a;  //модуль числа r, и аргумент a
};

//функция вводит комплексное число с именем name
Complex nextComplex(string name) {
	cout << "Введите " << name << ": ";
	double r, a;
	cin >> r >> a;
	return Complex(r, a);
}

int main() {
	//устанавливаем вывод кириллицы
	setlocale(LC_ALL, "Russian");

	//вводим числа
	Complex a = nextComplex("a");
	Complex b = nextComplex("b");
	Complex c = nextComplex("c");
	Complex d = nextComplex("d");

	//вычисление R согласно формуле
	Complex R = b.pow(3).add(a.add(b).div(c.sub(a)).mult(d));

	//вывод R в двух формах
	cout << "\nR = "; R.print_alg();
	cout << "\nR = "; R.print_tr();
	cout << '\n';

	return 0;
}
