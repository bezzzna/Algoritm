#include <iostream>
#define M 100
#define N 4
using namespace std;

class suanshu
{
	int count, length;
	char number[N], n;
	long double chance[N], c;
	char code[M];
	long double High, Low, high, low, d;
public:
	suanshu()
	{
		High = 0; Low = 0;
	}
	void get_number();
	void get_code();
	void coding();
	void decoding();
	~suanshu() {}// Это функция деструктора, для очистки памяти.
};

void suanshu::get_number()
{
	cout << "введите букву и ее вероятность:" << endl;
	int i = 0;
	for (; i < N; i++)
	{
		cin >> n >> c;
		number[i] = n;
		chance[i] = c;
	}
	if (i == 20) {
		cout << "the number is full." << endl;
	}
	count = i;
}

void suanshu::get_code()
{
	cout << "укажите длину:";
	cin >> length;
	while (length >= M)
	{
		cout << "длина слишком большая, введите меньше:";
		cin >> length;
	}
	cout << "Код вывода:";
	for (int i = 0; i < length; i++)
	{
		cin >> code[i];
	}
}

void suanshu::coding()
{
	// Находим интервал кодирования первого символа
	int i, j = 0;
	
	for (i = 0; i < count; i++)// Оценка первого символа подстрочного индекса
		if (code[0] == number[i]) break;
	while (j < i)// Находим верхнюю и нижнюю границы вероятностного интервала первого символа
		Low += chance[j++];
	d = chance[j];
	High = Low + d;
	
	

	for (i = 1; i < length; i++)
		for (j = 0; j < count; j++)
		{
			
			if (code[i] == number[j])
			{
				if (j == 0)
				{
					low = Low;
					high = Low + chance[j] * d;
					High = high;
					d *= chance[j];
					
				}
				else
				{
					long double chance_l = 0.0;
					for (int k = 0; k <= j - 1; k++)
						chance_l += chance[k];
					low = Low + d * chance_l;
					high = Low + d * (chance_l + chance[j]);
					Low = low;
					High = high;
					d *= chance[j];
					
					
					
				}
			}
			else continue;
		}
	cout << "the result is:" << Low << endl;
}
void suanshu::decoding()
{   // Low=(Low+High)/2;
	int i, j;
	char out[100];// Количество декодируемых символов не превышает 100
	for (i = 0; i < length; i++)// Расшифровать символы по одному
	{

		long double m0 = 0.0;
		long double m1 = 0.0;
		for (j = 0; j < count; j++)
		{
			// Постоянно меняем интервал кодирования для оценки
			m0 = m1;
			m1 = m0 + chance[j];
			//cout<<Low<<m0<<m1<<endl;
			if ((Low >= m0) && (Low < m1))// Low - конечный результат арифметического кодирования
			{
				out[i] = number[j];
				Low -= m0;
				Low = Low / (chance[j]);
				break;
			}
			continue;// Символов нет в словаре
		}

		cout << out[i];
	}
	cout << endl;
}


int main()
{
	
	setlocale(LC_ALL, "Russian");
	suanshu a;
	a.get_number();// Получаем символы и вероятность
	a.get_code();// Получаем строку для кодирования
	a.coding();//Кодируем
	a.decoding();//Декодирование

	
	return 0;
}
