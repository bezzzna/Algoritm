#include <iostream>
#include "lib.h"
#include <string>

using namespace std;

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "Russian");
	cout<<"Введите длину сообщения:\n";
	int n;
	string message;
	cin>>n;
	string m;
	for (int i=0; i<n; i++) //рандомная генерация сообщения (используется для тестов)
	{
		m=char('a' + rand() % ('z' - 'a'));
		message+=m;
	}
	double length = message.length(); 
	cout<<"Полученное сообщение:\n"<<message<<"\n";
	cout<<"Длина введённого сообщения: "<<message.length()<<"\n";
	double *ver = new double[message.length()]; //вероятности 
	double *vgran = new double[message.length()]; //верх границы
	double *ngran = new double[message.length()+1]; //низ границы
	string std = generate(n, message, ver, vgran, ngran);  //составление алфавита, подсчёт вероятности, вычисление границ
	cout<<"\nБуква:"<<"\t"<<"Вероятность:\t Ниж.граница: \t Верх.граница:\n";
	for (int i=0; i<std.length(); i++)
		cout<<std[i]<<"\t"<<ver[i]<<"\t\t "<<ngran[i]<<"\t\t "<<vgran[i]<<"\n";
	double Low = coding(ngran, vgran, std);
	cout<<"\nЗакодированное сообщение:"<<Low;
	string message1 = decoding (Low, ver, std, message.length());
	cout<<"\nПолученное сообщение после декодирования:\n"<<message1<<"\n";
	//После декодирования кода можно получить сообщение, отличающееся некоторыми символами, т.к границы из-за 
	//окгруления повторяются. (Для успешной проверки работы декодирования нужно брать не слишком большое сообщение при кодировании).
	return 0;
}
