#pragma once
#ifdef __APPLE__
#else

using namespace std;
class Obj_Loading
{
    public:
        Obj_Loading(string);
        void createObject();
    private:
        string filename = "";
        vector<vector<float>*>* vertices = new vector<vector<float>*>;
        vector<vector<int>*>* faceCoordinates = new vector<vector<int>*>;
        vector<string>* splitStrings(char, string);
        float getCoordinateDigits(string);
        float* normals(float*, float*, float*);
};

#endif 
