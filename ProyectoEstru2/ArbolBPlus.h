#pragma once
#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Producto;

class NodoBPlus {
public:
    bool esHoja;
    std::vector<std::string> claves;
    std::vector<Producto*> valores;
    std::vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;

    NodoBPlus(bool hoja) : esHoja(hoja), siguiente(nullptr) {}
};

class ArbolBPlus {
private:
    NodoBPlus* raiz;
    int orden;

    void insertarEnNodoInterno(const std::string& clave, NodoBPlus* nodo, NodoBPlus* hijoDerecho);
    void dividirNodoInterno(NodoBPlus* nodo);
    NodoBPlus* encontrarPadre(NodoBPlus* actual, NodoBPlus* hijo);
    void dividirHoja(NodoBPlus* nodo);

public:
    ArbolBPlus(int _orden) : orden(_orden), raiz(new NodoBPlus(true)) {}

    void insertar(const std::string& clave, Producto* producto);
    Producto* buscar(const std::string& clave);
    void recorrer();
};

#endif // ARBOLBPLUS_H