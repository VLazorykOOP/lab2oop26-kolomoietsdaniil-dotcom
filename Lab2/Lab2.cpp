// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#if !defined(_MSC_VER)
#define VS_CODE
#endif
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
#include <clocale>
#include <string.h>
#if !defined(VS_CODE)
#include <Windows.h>
#endif

// 1. Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.

void Task_1()
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


// Функція шифрування

void my_encryption (std::string text, unsigned short OutCoding[128]) {
	// 1. Доповнення пробілами до 128 символів
	while (text.length() < 128) {
		text += ' ';
	}
	// 2. Змінні для обробки символів та формування 16-бітного числа
	unsigned char c;
	unsigned short r, t, i, b;
	short j;

	// 3. Шифрування кожного символу
	for (i = 0; i < 128; i++) {
		r = 0;      // Тут будемо формувати наші 16 бітів (початково всі нулі)
		c = text[i];             
		t = c;                  
		r |= (t >> 4); 
		r |= (i << 4);
		t = c;
		r |= ((t & 0x0F) << 11);
		t = 1;
		b = 0;
		for (j = 0; j < 16; j++)         
		{
			if (r & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b << 15;                    
		OutCoding[i] = r;
	}
}

// 2 спосіб - використання структури з бітовими полями
struct TextCode {
	unsigned short schkb  : 4; // Біти 0-3: старша частина ASCII
	unsigned short posrow : 7; // Біти 4-10: позиція символу
	unsigned short mchkb  : 4; // Біти 11-14: молодша частина ASCII
	unsigned short bitp   : 1; // Біт 15: біт парності
};

unsigned char pbit(unsigned char c)
{

	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}
void My_EncryptionU(std::string text, TextCode OutCoding[128])
{
	while (text.length() < 128) {
		text += ' ';
	}

	unsigned char c;
	unsigned short r, t, i;
	short j;
	
	for (i = 0; i < 128; i++)  {
		c = text[i];
		OutCoding[i].schkb = c >> 4;
		OutCoding[i].mchkb = c & 0x0f;
		OutCoding[i].posrow = i;
		r = pbit(c);
		t = pbit(static_cast<unsigned char>(i));
		OutCoding[i].bitp = r ^ t;
	}
}



	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		// Тестовий рядок (менше 128 символів, щоб перевірити доповнення пробілами)
		std::string myText = "Лабораторна робота №1";
		unsigned short encryptedArray[128];
		TextCode encryptedStructArray[128];

		// Викликаємо нашу функцію шифрування
		my_encryption(myText, encryptedArray);

		std::cout << "Початковий текст: \"" << myText << "\"\n";
		std::cout << "Зашифровані дані (перші 20 символів у шістнадцятковому форматі):\n";
		std::cout << "1 Спосіб (без структур):\n";

		// Виводимо результат для перевірки (у HEX форматі, щоб було видно структуру бітів)
		for (int i = 0; i < 20; i++) {
			std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
				<< encryptedArray[i] << " ";
		}
		std::cout << "\n";

		// Викликаємо нашу функцію шифрування
		My_EncryptionU(myText, encryptedStructArray);
		std::cout << "2 Спосіб (за допомогою структури):\n";
		for (int i = 0; i < 20; i++) {
			unsigned short outValue;
			// Копіюємо пам'ять структури у звичайне число для виведення на екран
			memcpy(&outValue, &encryptedArray[i], sizeof(unsigned short));
			std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
				<< outValue << " ";
		}
		std::cout << "\n";

		return 0;

	}
