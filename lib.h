#ifndef lib_H
#define lib_H

#include <string>

std::string generate(int n, std::string message, double *ver, double *vgran, double *ngran); //����������� ��������, ������� �����������, ���������� ������
std::string decoding(double LOW, double *ver, std::string std, int length); //������� �������������
double coding(double *ngran, double *vgran, std::string std); //������� ����������� ���������

#endif
