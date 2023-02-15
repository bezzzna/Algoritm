#include "lib.h"
#include <iostream>

#include <string>

using namespace std;

string generate(int n, string message, double *ver, double *vgran, double *ngran) //����������� ��������, ������� �����������, ���������� ������
{
	string std = ""; //������ ������ ������ ��� ��������
	int k=-1; //���� ��� �������� (���� �� ������ � �������� ��� ���)
	//���������� �������
	for (int i = 0; i < message.length(); i++)  //���� �� ���������
	{
		k=std.find(message[i]); //����� ������� � ��������
        if (k==(-1)) //�������� �� ��, ������ �� ������ � �������� ��� ���
		{
        	std+=message[i]; //��������� ������ � �������
		}
    }
	ngran[0]=0; //����� ������ ������� 
	double length = message.length();  //������� ����� ���������
	for (int i=0; i<std.length(); i++) //���������� ������ � ������� ������
	{
		int perem=0; //������� ���-�� ��������� �������� �� �������� � ���������
		for (int j=0; j<message.length(); j++) //���� �������� ��������
		{
			if (std[i]==message[j])
				perem++;
		}
		ver[i]=perem/length; //����������� �����������
		vgran[i]=ngran[i]+ver[i]; //������� ������� ������� � ������
		ngran[i+1]=vgran[i]; //������� ������ ������� � ������
	}
	return std; //���������� ������� 
}

double coding(double *ngran, double *vgran, string std) //������� ����������� ���������
{
	double low = 0, high = 1; //��������� �������
	double *vgran1 = new double[std.length()]; //���� �������
	double *ngran1 = new double[std.length()]; //��� �������
	cout<<"\n������:\t ������ �������: \t ������� �������: \n";
	for (int i=0; i<std.length(); i++) //���������� ����/��� ������ �����������
	{
		ngran1[i]=low+ngran[i]*(high-low); //������� ���.�������
		vgran1[i]=low+vgran[i]*(high-low); //������� ����.�������
		high=vgran1[i]; //���������� ���. ������� ����
		low=ngran1[i];  //���������� ���. ������� ���
		cout<<std[i]<<"\t"<<ngran1[i]<<"\t\t"<<vgran1[i]<<"\n"; //�����
	}
	return ngran1[std.length()-1]; //���������� ��� ���������
}

string decoding(double LOW, double *ver, string std, int length) //������� �������������
{
	string message1=""; //������ ������ ��� �������������
	for (int i=0; i<length; i++) //���� ��� ���������� ��������������� ���������
	{
		double m0=0.0, m1=0.0; //��������� �������� ��� �������� �� �������� (��������)
		for (int j=0; j<std.length(); j++) //���� �� �������� 
		{
			m0=m1; //���������� ������� 
			m1=m0+ver[j]; //����������� �����
			if (LOW>=m0 && LOW<m1) //�������, ������ �� ����������� ������� ���� � ��������� ��������������� ���������
			{
				message1+=std[j]; //���� ��, �� ���������� ��������� �����
				LOW-=m0; //�������� ������� �� ��������������� ��������� (����)
				LOW=LOW/ver[j]; //��������� 
				break; //��������� ���� 
			} 
			continue;
		}
	}
	return message1; //���������� �������������� ���������
}
