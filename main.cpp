#include <iostream>
#include "lib.h"
#include <string>

using namespace std;

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "Russian");
	cout<<"������� ����� ���������:\n";
	int n;
	string message;
	cin>>n;
	string m;
	for (int i=0; i<n; i++) //��������� ��������� ��������� (������������ ��� ������)
	{
		m=char('a' + rand() % ('z' - 'a'));
		message+=m;
	}
	double length = message.length(); 
	cout<<"���������� ���������:\n"<<message<<"\n";
	cout<<"����� ��������� ���������: "<<message.length()<<"\n";
	double *ver = new double[message.length()]; //����������� 
	double *vgran = new double[message.length()]; //���� �������
	double *ngran = new double[message.length()+1]; //��� �������
	string std = generate(n, message, ver, vgran, ngran);  //����������� ��������, ������� �����������, ���������� ������
	cout<<"\n�����:"<<"\t"<<"�����������:\t ���.�������: \t ����.�������:\n";
	for (int i=0; i<std.length(); i++)
		cout<<std[i]<<"\t"<<ver[i]<<"\t\t "<<ngran[i]<<"\t\t "<<vgran[i]<<"\n";
	double Low = coding(ngran, vgran, std);
	cout<<"\n�������������� ���������:"<<Low;
	string message1 = decoding (Low, ver, std, message.length());
	cout<<"\n���������� ��������� ����� �������������:\n"<<message1<<"\n";
	//����� ������������� ���� ����� �������� ���������, ������������ ���������� ���������, �.� ������� ��-�� 
	//���������� �����������. (��� �������� �������� ������ ������������� ����� ����� �� ������� ������� ��������� ��� �����������).
	return 0;
}
