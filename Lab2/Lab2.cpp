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
		for (j = 0; j < 16; j++)  // обчислення біта парності для символу та позиції        
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
int my_decryption(unsigned short InCoding[128], char OutS[128]) { 
	unsigned char c;
	unsigned short r, t, i, b, p, w;
	short j;

	// Очищуємо вихідний масив (заповнюємо нулями, щоб рядок коректно завершувався)
	for (i = 0; i < 129; i++) {
		OutS[i] = 0;
	}

	for (i = 0; i < 128; i++) {
		r = InCoding[i];
		t = r & 0b0111111111111111; // 0x7FFF
		p = (r & 0b1000000000000000) >> 15; // 0x8000
		w = 1;
		b = 0;
		for (j = 0; j < 16; j++) {
			if (t & w) {
				if (b == 0) b = 1; else b = 0;
			}
			w <<= 1;
		}
		if (p != b) return -i;
		t = r & 0b0000000000001111; // 0x000F
		t <<= 4;
		w = r & 0b0111100000000000; // 0x7800
		w >>= 11;
		unsigned char c = t | w;
		unsigned short pos = r & 0b0000011111110000; // 0x07F0
		pos >>= 4;
		OutS[pos] = c;
	}

	return 1; 
}

void TaskTask_4()
{
	long long x, y, s_1, s_2;
	cout << "Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.\n";
	cout << "Вираз : s = (20 * y - x * 120) / 32 + (x + 32 * y) / 128 + (x + y) % 16\n";
	cout << "Введiть x: \n";
	cin >> x;
	cout << "Введiть y: \n";
	cin >> y;

	auto st = cin.rdstate();
	if (st != cin.goodbit) {
		cin.clear(); cout << " error \n"; cin.get(); cin.get(); cin.get(); cin.get();
		return;
	}
	s_1 = (20 * y - x * 120) / 32 + (x + 32 * y) / 128 + (x + y) % 16;
	s_2 = ((((y << 4) + (y << 2)) - ((x << 7) - (x << 3))) >> 5) + ((x + (y << 5)) >> 7) + ((x + y) & 15);
	cout << "\nx=" << x << "\ny=" << y << "\ns_1=" << s_1 << "\ns_2=" << s_2 << endl;
	cin.get();
	cin.get();
	return;
}




	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		int choice; // Змінна для зберігання вибору користувача в головному меню
		do {
			std::cout << "\n================ ГОЛОВНЕ МЕНЮ ================\n";
			std::cout << "1. Обчислення виразу з використанням побітових операцій  \n";
			std::cout << "2. Шифрування тексту та подальше дешифрування\n";
			std::cout << "3. Шифрування тексту (за допомогою структури) та подальше дешифрування\n";
			std::cout << "4. Завдання 4 (Обчислення виразу з використанням побітових операцій)\n";
			std::cout << "0. Вихід з програми\n";
			std::cout << "==============================================\n";
			std::cout << "Ваш вибір: ";
			std::cin >> choice; // Зчитуємо вибір користувача

			std::cout << "\n"; // Порожній рядок для краси

			switch (choice) { // Виконуємо відповідну функцію залежно від вибору користувача
			case 1:
				std::cout << "1 Завдання\n";
				Task_1();
				break;
			case 2: {
				std::cout << "2 Завдання\n";
				std::string myText;
				std::cout << "Введіть текст для шифрування (до 128 символів): ";
				std::cin.ignore(); 
				std::getline(std::cin, myText); 
				unsigned short encryptedArray[128];
				TextCode encryptedStructArray[128];
				my_encryption(myText, encryptedArray);

				std::cout << "Початковий текст: \"" << myText << "\"\n";
				std::cout << "1 Спосіб:\n";
				std::cout << "Зашифровані дані:\n";

				
				for (int i = 0; i < myText.length(); i++) {
					std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
						<< encryptedArray[i] << " ";
				}
				std::cout << "\n";

				char decryptedText[129]; // +1 для нуль-термінатора

				int result = my_decryption(encryptedArray, decryptedText);

				if (result == 1) {
					std::cout << "Текст успішно розшифровано:\n";
					std::cout << decryptedText << "\n";
				}
				else {
					std::cout << "Помилка розшифрування! Дані пошкоджено на індексі: " << -result << "\n";
				}
				std::cout << "\n";

				break;
			}
			case 3: {
				std::cout << "3 Завдання\n";
				std::string myText;
				std::cout << "Введіть текст для шифрування (до 128 символів): ";
				std::cin.ignore(); // Очищуємо буфер від 'Enter', що залишився після вибору в меню
				std::getline(std::cin, myText); // Зчитуємо весь рядок разом із пробілами
				unsigned short encryptedArray[128];
				TextCode encryptedStructArray[128];
				My_EncryptionU(myText, encryptedStructArray);
				std::cout << "2 Спосіб (за допомогою структури):\n";
				std::cout << "Зашифровані дані:\n";
				for (int i = 0; i < myText.length(); i++) {
					unsigned short outValue;
					// Копіюємо пам'ять структури у звичайне число для виведення на екран
					memcpy(&outValue, &encryptedStructArray[i], sizeof(unsigned short));
					std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
						<< outValue << " ";
				}
				std::cout << std::dec << "\n\n";

				unsigned short tempArray[128];
				for (int i = 0; i < myText.length(); i++) {
					memcpy(&tempArray[i], &encryptedStructArray[i], sizeof(unsigned short));
				}
				char decryptedText[129];
				int result = my_decryption(tempArray, decryptedText);

				if (result == 1) {
					// Обрізаємо зайві пробіли (щоб лапки не відлітали)
					int len = strlen(decryptedText);
					while (len > 0 && decryptedText[len - 1] == ' ') {
						decryptedText[len - 1] = '\0';
						len--;
					}
					std::cout << "Текст успішно розшифровано:\n\"" << decryptedText << "\"\n";
				}
				else {
					std::cout << "Помилка розшифрування на індексі: " << -result << "\n";
				}
				break;
			}
			case 4: {
				std::cout << "4 Завдання\n";
				TaskTask_4();
				break;
			}
			case 0:
				std::cout << "Роботу завершено.\n";
				break;
			default:
				std::cout << "Помилка: Невірний вибір. Введіть число від 0 до 3.\n";
			}
		} while (choice != 0);
	
		return 0;

	}
