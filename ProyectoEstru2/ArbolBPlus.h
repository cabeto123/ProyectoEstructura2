#pragma once
#include "NodoBPlus.h"
#include <iostream>
class ArbolBPlus
{
private:
    NodoBPlus* raiz;
    int orden;
    void insertarEnNodoInterno(const string& clave, NodoBPlus* nodo, NodoBPlus* hijoDerecho);
    void dividirNodoInterno(NodoBPlus* nodo);
    NodoBPlus* encontrarPadre(NodoBPlus* actual, NodoBPlus* hijo);
    void dividirHoja(NodoBPlus* nodo);
    public:
        ArbolBPlus(int _orden) : orden(_orden), raiz(new NodoBPlus(true)) {}
        void insertar(const string& clave);
        void recorrer();
};

