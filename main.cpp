#include <iostream>
#include "lib.h"
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int main(int argc, char** argv) 
{	
	//часть кода для тестирования
	ofstream out;
	for (int iter = 0; iter < 30; iter++)
	{
		string iters = to_string(iter);
		out.open(iters+" - in.txt");
		setlocale(LC_ALL, "Russian");
		cout << "Введите длину сообщения:\n";
		int n;
		string message;
		cin >> n;
		string m;
		for (int i = 0; i < n; i++) //рандомная генерация сообщения (используется для тестов)
		{
			m = char('a' + rand() % ('z' - 'a'));
			message += m;
		}
		
		double length = message.length();
		cout << "Полученное сообщение:\n" << message << "\n";
		cout << "Длина введённого сообщения: " << message.length() << "\n";
		double* ver = new double[message.length()]; //вероятности 
		double* vgran = new double[message.length()]; //верх границы
		double* ngran = new double[message.length() + 1]; //низ границы
		string std = generate(n, message, ver, vgran, ngran);  //составление алфавита, подсчёт вероятности, вычисление границ
		//cout << "\nБуква:" << "\t" << "Вероятность:\t Ниж.граница: \t Верх.граница:\n";
		out << "Сообщение на входе: " << message;
		out.close();
		out.open(iters + " - out.txt");
		out << "\nБуква:" << "\t" << "Вероятность:\t Ниж.граница: \t Верх.граница:\n";
		for (int i = 0; i < std.length(); i++)
		{
			//cout << std[i] << "\t" << ver[i] << "\t\t " << ngran[i] << "\t\t " << vgran[i] << "\n";
			out << std[i] << "\t" << ver[i] << "\t\t " << ngran[i] << "\t\t " << vgran[i] << "\n";
		}
		auto start = chrono::steady_clock::now();//получаем начальный момент времени
		double Low = coding(ngran, vgran, std);
		auto stop = chrono::steady_clock::now();//получаем конечный момент времени
		out << "Закодированное сообщение:" << Low;
		out << "\nCODING TIME: " << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << " nanoseconds" << endl;//вывод времени выполнения кодирования
		//cout << "\nЗакодированное сообщение:" << Low;
		start = chrono::steady_clock::now();//получаем начальный момент времени
		string message1 = decoding(Low, ver, std, message.length());
		stop = chrono::steady_clock::now();//получаем конечный момент времени
		//cout << "\nПолученное сообщение после декодирования:\n" << message1 << "\n";
		out << "\nПолученное сообщение после декодирования:\n" << message1 << "\n";
		out << "\nDECODING TIME: " << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << " nanoseconds" << endl;//вывод времени выполнения кодирования
		out.close();
		//После декодирования кода можно получить сообщение, отличающееся некоторыми символами, т.к границы из-за 
		//окгруления повторяются. (Для успешной проверки работы декодирования нужно брать не слишком большое сообщение при кодировании).
	}
	return 0;
}
