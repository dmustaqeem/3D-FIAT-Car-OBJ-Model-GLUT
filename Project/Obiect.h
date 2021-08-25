#ifndef OBIECT_H
#define OBIECT_H

class Obiect
{
private:
	double x;
	double y;
	double z;
public:
	Obiect(double, double, double);
	Obiect();
	void setx(double a);
	void sety(double a);
	void setz(double a);
	double getx();
	double gety();
	double getz();
	virtual void Draw() = 0;
};


#endif