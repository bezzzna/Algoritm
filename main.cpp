#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

using namespace std::chrono;

string generate(int n, string message, double* ver, double* vgran, double* ngran) //составление алфавита, подсчёт вероятности, вычисление границ
{
	string std = ""; //создаём пустую строку для алфавита
	int k = -1; //флаг для проверки (есть ли символ в алфавите или нет)
	//составляем алфавит
	for (int i = 0; i < message.length(); i++)  //цикл по сообщению
	{
		k = std.find(message[i]); //поиск символа в алфавите
		if (k == (-1)) //проверка на то, найден ли символ в алфавите или нет
		{
			std += message[i]; //добавляем символ в алфавит
		}
	}
	ngran[0] = 0; //задаём нижнию границу 
	double length = message.length();  //находим длину сообщения
	for (int i = 0; i < std.length(); i++) //нахождение нижних и верхних границ
	{
		int perem = 0; //подсчёт кол-ва вхождений символов их алфавита в сообщение
		for (int j = 0; j < message.length(); j++) //цикл подсчёта символов
		{
			if (std[i] == message[j])
				perem++;
		}
		ver[i] = perem / length; //высчитываем вероятность
		vgran[i] = ngran[i] + ver[i]; //заносим верхнюю границу в массив
		ngran[i + 1] = vgran[i]; //заносим нижнюю границу в массив
	}
	return std; //возвращаем алфавит 
}


double coding(double* ngran, double* vgran, string std) //функция кодирования сообщения
{
	double low = 0, high = 1; //начальные условия
	double* vgran1 = new double[std.length()]; //верх границы
	double* ngran1 = new double[std.length()]; //низ границы
	cout << "\nСимвол:\t Нижняя граница: \t Верхняя граница: \n";
	for (int i = 0; i < std.length(); i++) //нахождение верх/ниж границ кодирования
	{
		ngran1[i] = low + ngran[i] * (high - low); //формула ниж.границы
		vgran1[i] = low + vgran[i] * (high - low); //формула верх.границы
		high = vgran1[i]; //запоминаем выч. границу верх
		low = ngran1[i];  //запоминаем выч. границу ниж
		cout << std[i] << "\t" << ngran1[i] << "\t\t" << vgran1[i] << "\n"; //вывод
	}
	return ngran1[std.length() - 1]; //возвращаем код сообщения
	
}

string decoding(double LOW, double* ver, string std, int length) //функция декодирования
{
	string message1 = ""; //пустая строка для декодирования
	for (int i = 0; i < length; i++) //цикл для нахождения декодированного сообщения
	{
		double m0 = 0.0, m1 = 0.0; //начальные значения для движений по алфавиту (границам)
		for (int j = 0; j < std.length(); j++) //цикл по алфавиту 
		{
			m0 = m1; //запоминаем границу 
			m1 = m0 + ver[j]; //высчитываем новую
			if (LOW >= m0 && LOW < m1) //смотрим, входят ли вычисленные границы букв в интеравал закодированного сообщения
			{
				message1 += std[j]; //если да, то записываем найденную букву
				LOW -= m0; //вычитаем границу из закодированного сообщения (кода)
				LOW = LOW / ver[j]; //вычисляем 
				break; //прерываем цикл 
			}
			continue;
		}
	}
	return message1; //возвращаем декодированное сообщение
}

int main()
{
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
	cout << "\nБуква:" << "\t" << "Вероятность:\t Ниж.граница: \t Верх.граница:\n";
	for (int i = 0; i < std.length(); i++)
		cout << std[i] << "\t" << ver[i] << "\t\t " << ngran[i] << "\t\t " << vgran[i] << "\n";

	auto start = high_resolution_clock::now();//получаем начальный момент времени

	double Low = coding(ngran, vgran, std);//вызывваем функцию кодирования

	auto stop = high_resolution_clock::now();//получаем конечный момент времени
	auto duration = duration_cast<milliseconds>(stop - start);//вычисляем разницу начала и конца (продолжительность)

	cout << "CODING TIME: "<< duration.count() << " milliseconds" << endl;//вывод времени выполнения кодирования

	cout << "\nЗакодированное сообщение:" << Low;

	start = chrono::steady_clock::now();

	string message1 = decoding(Low, ver, std, message.length());

	stop = chrono::steady_clock::now();;//получаем конечный момент времени

	cout << "\nDECODING TIME: " << chrono::duration_cast<chrono::nanoseconds>(stop - start).count() << " nanoseconds" << endl;//вывод времени выполнения кодирования


	cout << "\nПолученное сообщение после декодирования:\n" << message1 << "\n";

	
	//После декодирования кода можно получить сообщение, отличающееся некоторыми символами, т.к границы из-за 
	//окгруления повторяются. (Для успешной проверки работы декодирования нужно брать не слишком большое сообщение при кодировании).
}
