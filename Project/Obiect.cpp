#include "Obiect.h"


Obiect::Obiect(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Obiect::Obiect() {}

void Obiect::setx(double a)
{
	x = a;
}

void Obiect::sety(double a)
{
	y = a;
}

void Obiect::setz(double a)
{
	z = a;
}

double Obiect::getx()
{
	return x;
}

double Obiect::gety()
{
	return y;
}

double Obiect::getz()
{
	return z;
}