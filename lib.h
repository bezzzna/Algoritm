#ifndef lib_H
#define lib_H

#include <string>

std::string generate(int n, std::string message, double *ver, double *vgran, double *ngran); //составление алфавита, подсчёт вероятности, вычисление границ
std::string decoding(double LOW, double *ver, std::string std, int length); //функция декодирования
double coding(double *ngran, double *vgran, std::string std); //функция кодирования сообщения

#endif
