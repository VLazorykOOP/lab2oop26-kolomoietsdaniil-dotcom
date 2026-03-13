// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#if !defined(_MSC_VER)
#define VS_CODE
#endif
#include <fstream>
using namespace std;
#include <clocale>
#include <string.h>
#if !defined(VS_CODE)
#include <Windows.h>
#endif

void Example2()
{
	long long a, b, c, d ,x, y;
	cout << "Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.\n";
	cout << "Вираз : x = 37 * b + (d * 31 + a * 12) / 2048 -  65 * c + d*14 \n";
	cout << "Введiть a: \n";
	cin >> a;
	cout << "Введiть b: \n";
	cin >> b;
	cout << "Введiть c: \n";
	cin >> c;
	cout << "Введiть d: \n"; 
	cin >> d;

	auto st = cin.rdstate();
	if (st != cin.goodbit) {
		cin.clear(); cout << " error \n"; cin.get(); cin.get(); cin.get(); cin.get();
		return;
	}
	y = (37 * b) + ((d * 31 + a * 12) / 2048) -  (65 * c) + (d * 14);
	x =	((b << 5) + (b << 2) + b) +
		(((d << 5) - d + (a << 3) + (a << 2)) >> 11) -
		((c << 6) + c) +
		((d << 4) - (d << 1));
	cout << "\nx=" << x << "\ny=" << y << "\na=" << a << "\nb=" << b << "\nc=" << c << "\nd=" << d << endl;
	cin.get();
	cin.get();
	return;
}


	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		Example2();
	}

