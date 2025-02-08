#pragma once
#include <vector>
#include <string>
using namespace std;
class NodoBPlus
{
    public:
    bool esHoja;
    vector<string> claves;
    vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;

    NodoBPlus(bool hoja) : esHoja(hoja), siguiente(nullptr) {}
};

