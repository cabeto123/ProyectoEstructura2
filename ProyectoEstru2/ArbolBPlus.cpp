#include "ArbolBPlus.h"

void ArbolBPlus::insertarEnNodoInterno(const string& clave, NodoBPlus* nodo, NodoBPlus* hijoDerecho) {
    auto posicion = upper_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();
    nodo->claves.insert(nodo->claves.begin() + posicion, clave);
    nodo->hijos.insert(nodo->hijos.begin() + posicion + 1, hijoDerecho);

    if (nodo->claves.size() == 2 * orden - 1) {
        dividirNodoInterno(nodo);
    }
}


void ArbolBPlus::dividirNodoInterno(NodoBPlus* nodo) {
    int mitad = nodo->claves.size() / 2;
    string clavePromocionada = nodo->claves[mitad];

    NodoBPlus* nodoDerecho = new NodoBPlus(false);
    nodoDerecho->claves.assign(nodo->claves.begin() + mitad + 1, nodo->claves.end());
    nodoDerecho->hijos.assign(nodo->hijos.begin() + mitad + 1, nodo->hijos.end());

    nodo->claves.resize(mitad);
    nodo->hijos.resize(mitad + 1);

    if (nodo == raiz) {
        raiz = new NodoBPlus(false);
        raiz->claves.push_back(clavePromocionada);
        raiz->hijos.push_back(nodo);
        raiz->hijos.push_back(nodoDerecho);
    }
    else {
        insertarEnNodoInterno(clavePromocionada, encontrarPadre(raiz, nodo), nodoDerecho);
    }
}

NodoBPlus* ArbolBPlus::encontrarPadre(NodoBPlus* actual, NodoBPlus* hijo) {
    if (actual->esHoja || actual->hijos.empty()) return nullptr;

    for (auto* nodo : actual->hijos) {
        if (nodo == hijo) return actual;
    }

    for (auto* nodo : actual->hijos) {
        NodoBPlus* padre = encontrarPadre(nodo, hijo);
        if (padre) return padre;
    }
    return nullptr;
}

void ArbolBPlus::dividirHoja(NodoBPlus* nodo) {
    int mitad = nodo->claves.size() / 2;

    NodoBPlus* nodoDerecho = new NodoBPlus(true);
    nodoDerecho->claves.assign(nodo->claves.begin() + mitad, nodo->claves.end());
    nodo->claves.resize(mitad);

    nodoDerecho->siguiente = nodo->siguiente;
    nodo->siguiente = nodoDerecho;

    if (nodo == raiz) {
        raiz = new NodoBPlus(false);
        raiz->claves.push_back(nodoDerecho->claves[0]);
        raiz->hijos.push_back(nodo);
        raiz->hijos.push_back(nodoDerecho);
    }
    else {
        insertarEnNodoInterno(nodoDerecho->claves[0], encontrarPadre(raiz, nodo), nodoDerecho);
    }
}



void ArbolBPlus::insertar(const string& clave) {
    NodoBPlus* actual = raiz;

    while (!actual->esHoja) {
        auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
        actual = actual->hijos[posicion];
    }

    auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
    actual->claves.insert(actual->claves.begin() + posicion, clave);

    if (actual->claves.size() == 2 * orden - 1) {
        dividirHoja(actual);
    }
}

void ArbolBPlus::recorrer() {
    NodoBPlus* actual = raiz;
    while (!actual->esHoja) {
        actual = actual->hijos[0];
    }

    while (actual != nullptr) {
        for (const string& clave : actual->claves) {
            cout << clave << " ";
        }
        actual = actual->siguiente;
    }
    cout << endl;
}