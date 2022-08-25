#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Fellberg.h"

using namespace std;

double func(double x, double y)
{
	//return exp(x);
	//return y;
	return 3 * sin(2 * y) + x;
}


void Runge(double a, double b, double h, double *y0)
{
	double n = (b - a) / h;
	double *x = new double[n]; double *y = new double[n];
	double *k1 = new double[n]; double *k2 = new double[n]; double *k3 = new double[n]; double *k4 = new double[n]; double *k5 = new double[n]; double *k6 = new double[n]; double *k7 = new double[n]; double *k8 = new double[n]; double *k9 = new double[n]; double *k10 = new double[n]; double *k11 = new double[n]; double *k12 = new double[n]; double *k13 = new double[n];


	x[0] = a; y[0] = y0[0];

	for (int i = 1; i <= n; i++)
	{
		x[i] = a + i * h;
		k1[i] = func(x[i - 1], y[i - 1]);
		k2[i] = func(x[i - 1] + c2 * h, y[i - 1] + h * a2_1 * k1[i]);
		k3[i] = func(x[i - 1] + c3 * h, y[i - 1] + h * a3_1 * k1[i] + h * a3_2 * k2[i]);
		k4[i] = func(x[i - 1] + c4 * h, y[i - 1] + h * a4_1 * k1[i] + h * a4_2 * k2[i] + h * a4_3 * k3[i]);
		k5[i] = func(x[i - 1] + c5 * h, y[i - 1] + h * a5_1 * k1[i] + h * a5_2 * k2[i] + h * a5_3 * k3[i] + h * a5_4 * k4[i]);
		k6[i] = func(x[i - 1] + c6 * h, y[i - 1] + h * a6_1 * k1[i] + h * a6_2 * k2[i] + h * a6_3 * k3[i] + h * a6_4 * k4[i] + h * a6_5 * k5[i]);
		k7[i] = func(x[i - 1] + c7 * h, y[i - 1] + h * a7_1 * k1[i] + h * a7_2 * k2[i] + h * a7_3 * k3[i] + h * a7_4 * k4[i] + h * a7_5 * k5[i] + h * a7_6 * k6[i]);
		k8[i] = func(x[i - 1] + c8 * h, y[i - 1] + h * a8_1 * k1[i] + h * a8_2 * k2[i] + h * a8_3 * k3[i] + h * a8_4 * k4[i] + h * a8_5 * k5[i] + h * a8_6 * k6[i] + h * a8_7 * k7[i]);
		k9[i] = func(x[i - 1] + c9 * h, y[i - 1] + h * a9_1 * k1[i] + h * a9_2 * k2[i] + h * a9_3 * k3[i] + h * a9_4 * k4[i] + h * a9_5 * k5[i] + h * a9_6 * k6[i] + h * a9_7 * k7[i] + h * a9_8 * k8[i]);
		k10[i] = func(x[i - 1] + c10 * h, y[i - 1] + h * a10_1 * k1[i] + h * a10_2 * k2[i] + h * a10_3 * k3[i] + h * a10_4 * k4[i] + h * a10_5 * k5[i] + h * a10_6 * k6[i] + h * a10_7 * k7[i] + h * a10_8 * k8[i] + h * a10_9 * k9[i]);
		k11[i] = func(x[i - 1] + c11 * h, y[i - 1] + h * a11_1 * k1[i] + h * a11_2 * k2[i] + h * a11_3 * k3[i] + h * a11_4 * k4[i] + h * a11_5 * k5[i] + h * a11_6 * k6[i] + h * a11_7 * k7[i] + h * a11_8 * k8[i] + h * a11_9 * k9[i] + h * a11_10 * k10[i]);
		k12[i] = func(x[i - 1] + c12 * h, y[i - 1] + h * a12_1 * k1[i] + h * a12_2 * k2[i] + h * a12_3 * k3[i] + h * a12_4 * k4[i] + h * a12_5 * k5[i] + h * a12_6 * k6[i] + h * a12_7 * k7[i] + h * a12_8 * k8[i] + h * a12_9 * k9[i] + h * a12_10 * k10[i] + h * a12_11 * k11[i]);
		k13[i] = func(x[i - 1] + c13 * h, y[i - 1] + h * a13_1 * k1[i] + h * a13_2 * k2[i] + h * a13_3 * k3[i] + h * a13_4 * k4[i] + h * a13_5 * k5[i] + h * a13_6 * k6[i] + h * a13_7 * k7[i] + h * a13_8 * k8[i] + h * a13_9 * k9[i] + h * a13_10 * k10[i] + h * a13_11 * k11[i] + h * a13_12 * k12[i]);

		y[i] = y[i - 1] + h * (k1[i] * b1 + k2[i] * b2 + k3[i] * b3 + k4[i] * b4 + k5[i] * b5 + k6[i] * b6 + k7[i] * b7 + k8[i] * b8 + k9[i] * b9 + k10[i] * b10 + k11[i] * b11 + k12[i] * b12 + k13[i] * b13);

	}

	cout << "\nx0\ty\n";
	cout << "------------------\n";
	for (int i = 0; i <= n; i++)
	{
		cout << x[i] << "\t" << y[i] << endl << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b, h;

	cout << "Начало отрезка а = ";
	cin >> a;
	cout << "Конец отрезка b = ";
	cin >> b;
	cout << "Шаг h = ";
	cin >> h;

	double n = (b - a) / h;

	double *y = new double[n];

	cout << "Начальное условие y(0) = ";
	cin >> y[0];

	Runge(a, b, h, y);

	return 0;
}
