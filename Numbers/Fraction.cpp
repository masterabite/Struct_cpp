#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>


using namespace std;

int euclide(int n, int m);

class Fraction {
private:
	int nom;
	int den;

public:
	Fraction(char* str);
	Fraction(int n = 0, int m = 1) : nom(n), den(m) {};
	operator char* ();
	bool operator>=(Fraction& other);
	void reduce();	
};

Fraction::Fraction(char* str) {
	char* p = strchr(str, '/');
	den = 1;
	if (p != NULL) {
		*p++ = '\0';
		den = atoi(p);
	}
	nom = atoi(str);
}

Fraction::operator char* () {
	char* str = new char[32];
	sprintf(str, "%d/%d", nom, den);
	return str;
}

bool Fraction::operator>=(Fraction& other) {
	return nom * other.den >= other.nom * den;
}

void Fraction::reduce() {
	int k = euclide(nom, den);
	nom /= k;
	den /= k;
}

int euclide(int n, int m) {
	int r = 1;
	while (n != 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}

Fraction maxFraction(Fraction& f1, Fraction& f2) {

	if (f1>=f2) {
		cout << (char*)f1 << " >= " << (char*)f2 << '\n';
		return f1;
	}
	else {
		cout << (char*)f1 << " < " << (char*)f2 << '\n';
		return f2;
	}
}

int main(int argc, char* argv[]) {

	if (argc < 3) {
		return -1;
	}

	Fraction f1(argv[1]);
	Fraction f2(argv[2]);

	f1.reduce();
	f2.reduce();

	Fraction f_max = maxFraction(f1, f2);
	printf("maxFraction(%s, %s) = %s", (char*)f1, (char*)f2, (char*)f_max);
	return 0;
}
