#ifndef Masina_H
#define Masina_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "Obiect.h"
#include "Obj_Loading.h"

using namespace std;

class Masina : public Obiect
{
private:
	double rotireTun;
	double inclinareTun;
	double rotireMasina;
	string objFile;
	string tyreF;
	string fRTyre;
	string fLTyre;
	string bLTyre;
	float tVal = 0;
	bool ballF = false;
	Obj_Loading* object;
	Obj_Loading* tyreO;
	Obj_Loading* fRTyreO;
	Obj_Loading* fLTyreO;
	Obj_Loading* bLTyreO;
	float angle;
public:
	Masina(double a, double b, double c, double rt, double it, double rotireMasina);
	Masina();
	void fileData();
	void setFile();
	void setRotireTun(double);
	void setInclinareTun(double);
	void setRotireMasina(double);
	double getRotireTun();
	double getInclinareTun();
	double getRotireMasina();
	void incrementAngle();
	void decrementAngle();
	void Draw();

};

#endif