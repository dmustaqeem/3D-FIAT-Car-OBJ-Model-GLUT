#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Masina.h"
#include "Obiect.h"
#include <gl/freeglut.h>
#include <cmath>


Masina::Masina(double a, double b, double c, double rtun, double itun, double rtank) : Obiect(a, b, c)
{
	rotireTun = rtun;
	inclinareTun = itun;
	rotireMasina = rtank;

}

Masina::Masina() :Obiect() {}

void Masina::setRotireTun(double rtun)
{
	rotireTun = rtun;
}

void Masina::setInclinareTun(double itun)
{
	inclinareTun = itun;
}

void Masina::setRotireMasina(double rtank)
{
	rotireMasina = rtank;
}

double Masina::getRotireTun()
{
	return rotireTun;
}

double Masina::getInclinareTun()
{
	return inclinareTun;
}

double Masina::getRotireMasina()
{
	return rotireMasina;
}

void Masina::fileData()
{
	tyreF = "BackRightTyre.obj";
	objFile = "FiatFrame.obj";
	fRTyre = "FrontRightTyre.obj";
	fLTyre = "FrontLeftTyre.obj";
	bLTyre = "BackLeftTyre.obj";
	object = NULL;
	tyreO = NULL;
	fRTyreO = NULL;
	fLTyreO = NULL;
	bLTyreO = NULL;
}

void Masina::setFile()
{
	object = new Obj_Loading(objFile);

	tyreO = new Obj_Loading(tyreF);
	fRTyreO = new Obj_Loading(fRTyre);
	fLTyreO = new Obj_Loading(fLTyre);
	bLTyreO = new Obj_Loading(bLTyre);
}

void Masina::incrementAngle()
{
	angle -= 3.0;
}

void Masina::decrementAngle()
{
	angle += 3.0;
}

void Masina::Draw()
{
    if(tVal >= 0)
    {
        ballF = false;
    }
    else if(tVal <= -2)
    {
        ballF = true;
    }
	glPushMatrix();
	glTranslated(getx(), gety() - 1.0, getz());

	if(getz() < -20)
	{
		glTranslatef(0, 1, 0);
		glRotatef(180, 0, 0, 1);
	}
	else
	{
		glRotated(rotireMasina, 0, 1, 0);
		glRotated(rotireTun, 0, 1, 0);
		glRotated(inclinareTun, 1, 0, 0);
	}

	glPushMatrix();
	glColor3f(0.57, 0.38, 0);
	glNormal3f(1, 0, 0);
	object->createObject();
	glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 2.4, 0);
    if(ballF == false)
    {
        tVal -= 0.01;
    }
    else if(ballF == true)
    {
        tVal += 0.01;
    }
    glTranslatef(0, 0, tVal);
    glNormal3f(0, 0, 1);
    glColor3f(0, 1, 1);
    glutSolidSphere(0.5, 75, 80);
    glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.37, -1.60);
	glRotated(angle, 1, 0, 0);
	glTranslated(0, -0.37, 1.60);
	glColor3f(0.57, 0.38, 0);
	glNormal3f(1, 0, 0);
	tyreO->createObject();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0.465, 1.60);
	glRotated(angle, 1, 0, 0);
	glTranslated(0, -0.465, -1.60);
	glColor3f(0.57, 0.38, 0);
	glNormal3f(1, 0, 0);
	fRTyreO->createObject();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.465, 1.60);
	glRotated(angle, 1, 0, 0);
	glTranslated(0, -0.465, -1.60);
	glColor3f(0.57, 0.38, 0);
	glNormal3f(1, 0, 0);
	fLTyreO->createObject();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0.37, -1.60);
	glRotated(angle, 1, 0, 0);
	glTranslated(0, -0.37, 1.60);
	glColor3f(0.57, 0.38, 0);
	glNormal3f(1, 0, 0);
	bLTyreO->createObject();
	glPopMatrix();


	glPopMatrix();

}

Obj_Loading::Obj_Loading(string filename)
{
    this->filename = filename;
    fstream* objFile = new fstream;
    objFile->open(filename, ios_base::in);

    if (!objFile->is_open())
    {
        exit(EXIT_FAILURE);
    }

    string normalAndVertex;
    while (!objFile->eof())
    {
        getline(*objFile, normalAndVertex);

        vector<string>* coordinates = this->splitStrings(' ', normalAndVertex);

        if (coordinates->at(0) == "v")
        {
            //delete previous values stored in parameters and add new values 
            coordinates->erase(coordinates->begin());

            vector<float>* currentPoint = new vector<float>;
            for (int i = 0; i < coordinates->size(); i++)
            {
                currentPoint->push_back(this->getCoordinateDigits(coordinates->at(i)));
            }

            vertices->push_back(currentPoint);
        }
        else if (coordinates->at(0) == "f")
        {
            //Erase all the faces data and store new coordinates date 
            coordinates->erase(coordinates->begin());

            vector<int>* vertexIndexes = new vector<int>;
            for (int i = 0; i < coordinates->size(); i++)
            {       
                int faceIndex = this->getCoordinateDigits(coordinates->at(i));
                vertexIndexes->push_back(--faceIndex);
            }
            faceCoordinates->push_back(vertexIndexes);
        }

        delete coordinates;
    }

    objFile->close();
}

void Obj_Loading::createObject()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faceCoordinates->size(); i++)
    {
        float* nVal = NULL;
        float c1[3],c2[3],c3[3];

        for (int ii = 0; ii < (faceCoordinates->at(i))->size(); ii++)
        {
            int vertexInd = (faceCoordinates->at(i))->at(ii);

            if (ii == 0) {
                c1[0] = (vertices->at(vertexInd))->at(0);
                c1[1] = (vertices->at(vertexInd))->at(1);
                c1[2] = (vertices->at(vertexInd))->at(2);
            }
            else if (ii == 1) {
                c2[0] = (vertices->at(vertexInd))->at(0);
                c2[1] = (vertices->at(vertexInd))->at(1);
                c2[2] = (vertices->at(vertexInd))->at(2);
            }
            //Vertices arrays are complete we get all data now will render the Triangle using 3 Coordinates 
            else if(ii == 2){
                c3[0] = (vertices->at(vertexInd))->at(0);
                c3[1] = (vertices->at(vertexInd))->at(1);
                c3[2] = (vertices->at(vertexInd))->at(2);

                nVal = this->normals(c1, c2, c3);
                glNormal3f(nVal[0], nVal[1], nVal[2]);
                //c1 is coordinate 1 c2 is coordinate 2 and similarly 3 coordinate from object file 
                glVertex3f(c1[0], c1[1], c1[2]);
                glVertex3f(c2[0], c2[1], c2[2]);
                glVertex3f(c3[0], c3[1], c3[2]);
            }
        }
    }

    glEnd();
}

vector<string>* Obj_Loading::splitStrings(char seperator, string text)
{
    //Will use empty string to store new variable 
    string coord = "";
    text += seperator;
    vector<string>* charectars = new vector<string>;
    int ind = 0;
    while (ind < text.length())
    {
        if (text[ind] != seperator)
        {
            // will keep on adding the charectars untill reach seperator 
            coord += text[ind];
        }
        else
        {
            //In case of seperator will empty the string to again get a complete digit 
            charectars->push_back(coord);
            coord = "";
        }
        ind++;
    }
    return charectars;
}

float Obj_Loading::getCoordinateDigits(string coord)
{
    //stream to store all string dists in line in form of array
    istringstream arr(coord);
    float val;
    arr >> val;
    return val;
}
//TO store the normal vertices 
float* Obj_Loading::normals(float* c1, float* c2, float* c3)
{
    float vertexA[3], vertexB[3], abCross[3];

    vertexA[0] = c1[0] - c2[0];
    vertexA[1] = c1[1] - c2[1];
    vertexA[2] = c1[2] - c2[2];

    vertexB[0] = c1[0] - c3[0];
    vertexB[1] = c1[1] - c3[1];
    vertexB[2] = c1[2] - c3[2];

    // Using A * B - B * A for Cross multiplication of Coordinates 
    abCross[0] = vertexA[1] * vertexB[2] - vertexB[1] * vertexA[2];
    abCross[1] = vertexB[0] * vertexA[2] - vertexA[0] * vertexB[2];
    abCross[2] = vertexA[0] * vertexB[1] - vertexB[0] * vertexA[1];

    // Normalize Vector Using Square Root Function
    float normalizedV = sqrt(pow(abCross[0], 2) + pow(abCross[1], 2) + pow(abCross[2], 2));
    //Use float Array to store normal coodinates 
    float normalCoordinate[3];
    normalCoordinate[0] = abCross[0] / normalizedV;
    normalCoordinate[1] = abCross[1] / normalizedV;
    normalCoordinate[2] = abCross[2] / normalizedV;

    return normalCoordinate;
}
