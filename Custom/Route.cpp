#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

struct route {
	int id;
	string from, to, desc;
	int duration, interval;
}routes[100];

int routes_count; //кол-во маршрутов

string nextStr(ifstream& fin) {
	string str = "";
	char c = fin.get();
	while (c != ';' && c != '\n' && c != '\r') {
		if (fin.eof()) break; //если файл закончился, выходим
		str += c;
		c = fin.get();
	}
	return str;
}

int toInt(string str) {
	int ans = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		ans *= 10;
		ans += str[i] - '0';
	}
	return ans;
}

void scanFromFile(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		printf("Не удалось открыть файл.\n");
		return;
	}

	for (routes_count = 0; !fin.eof(); ++routes_count) {
		//считываем i-ую строку (информацию о маршруте)
		routes[routes_count].id = toInt(nextStr(fin));
		routes[routes_count].from = nextStr(fin);
		routes[routes_count].to = nextStr(fin);
		routes[routes_count].desc = nextStr(fin);
		routes[routes_count].duration = toInt(nextStr(fin));
		routes[routes_count].interval = toInt(nextStr(fin));
	}
}

void saveToFile(string filename) {
	ofstream fout(filename);
	for (int i = 0; i < routes_count; ++i) {
		fout << routes[i].id << ';' << routes[i].from << ';' << routes[i].to << ';'
			<< routes[i].desc << ';' << routes[i].duration << ';' << routes[i].interval;
	}
}

void printHeader() {
	printf("+--------+------------------+------------------+------------------------------------------+---------------+----------+\n");
	printf("| номер  | начальный пункт  |  конечный пункт  |                 описание                 |  длительность | интервал |\n");
	printf("+--------+------------------+------------------+------------------------------------------+---------------+----------+\n");
}

void printStr(int id) {
	printf("|%8d|%18s|%18s|%42s|%15d|%10d|\n", routes[id].id, routes[id].from.c_str(), routes[id].to.c_str(), routes[id].desc.c_str(), routes[id].duration, routes[id].interval);
	printf("+--------+------------------+------------------+------------------------------------------+---------------+----------+\n");
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	scanFromFile("f.in");

	//вывод таблицы
	printHeader();
	for (int i = 0; i < routes_count; ++i) {
		printStr(i);
	}


	cout << "Введите название конечного маршрута: ";
	string to;
	cin >> to;

	int cnt = 0; //для подсчета кол-во найденных маршрутов
	cout << "Номера найденных маршрутов: ";
	for (int i = 0; i < routes_count; ++i) {
		if (routes[i].to == to && routes[i].interval < 10) {
			cout << routes[i].id << ' ';
			++cnt;
		}
	}

	printf("\nНайдено маршрутов: %d\n", cnt);


	return 0;
}
