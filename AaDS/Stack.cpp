#include <iostream>
#include <locale>
#include <math.h>

using namespace std;

//структура элемента
struct node {
	int value; 
	node* next; //указатель на следующий элемент

	node(int _value) {
		value = _value;
		next = nullptr;
	}
};

//структура стека
struct myStack {
	node* top;
	
	myStack() {
		top = nullptr;
	}

	//добавляем элемент со значением value
	void add(int value) {
		node* newNode = new node(value);
		newNode->next = top;
		top = newNode;
	}

	//получаем верхний элемент (также удаляем его из стека)
	int pop() {
		if (top == nullptr) { return -1; }
		node* newTop = top->next;
		int val = top->value;
		delete top;
		top = newTop;
		return val;
	}

	//выводим стек
	void println() {
		for (node* cur = top; cur != nullptr; cur = cur->next) {
			cout << cur->value << ' ';
		}
		cout << '\n';
	}
};

//функция безопасно считывает целое число (int)
bool scan_int(int& i) {
	cin >> i;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Ошибка ввода!\n";
		return false;
	}
	return true;
}

//функция считывает стек
void scan_stack(myStack& s, int n) {
	int val;
	for (int i = 0; i < n;) {
		cout << "Введите " << n - i << " элемент(а/ов): ";
		while (i < n && scan_int(val)) {
			s.add(val);
			++i;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	//считываем размер очередей
	int n;
	do {
		cout << "Введите размер очередей: ";
	} while (!scan_int(n));

	//создаем три стека
	myStack s1, s2, s3;
	int val;

	//вводим первый стек
	cout << "Ввод первой очереди...\n";
	scan_stack(s1, n);

	//вводим второй стек
	cout << "Ввод второй очереди...\n";
	scan_stack(s2, n);
	
	cout << "Первая очередь: ";
	s1.println();

	cout << "Вторая очередь: ";
	s2.println();

	for (int i = 0; i < n; ++i) {
		s3.add(s1.pop());
		s3.add(s2.pop());
	}

	cout << "Новая очередь: ";
	s3.println();

}
