#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class NodoBPlus {
public:
    bool esHoja;
    vector<string> claves;
    vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;

    NodoBPlus(bool hoja) : esHoja(hoja), siguiente(nullptr) {}
};

class ArbolBPlus {
private:
    NodoBPlus* raiz;
    int orden;

    void insertarEnNodoInterno(const string& clave, NodoBPlus* nodo, NodoBPlus* hijoDerecho) {
        auto posicion = upper_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();
        nodo->claves.insert(nodo->claves.begin() + posicion, clave);
        nodo->hijos.insert(nodo->hijos.begin() + posicion + 1, hijoDerecho);

        if (nodo->claves.size() == 2 * orden - 1) {
            dividirNodoInterno(nodo);
        }
    }

    void dividirNodoInterno(NodoBPlus* nodo) {
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

    NodoBPlus* encontrarPadre(NodoBPlus* actual, NodoBPlus* hijo) {
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

    void dividirHoja(NodoBPlus* nodo) {
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

public:
    ArbolBPlus(int _orden) : orden(_orden), raiz(new NodoBPlus(true)) {}

    void insertar(const string& clave) {
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

    void recorrer() {
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
};

int main() {
    ArbolBPlus arbol(3);
    arbol.insertar("manzana");
    arbol.insertar("pera");
    arbol.insertar("uva");
    arbol.insertar("banana");
    arbol.insertar("kiwi");
    arbol.insertar("mango");
    arbol.insertar("durazno");
    arbol.insertar("fresa");

    cout << "Recorrido del Árbol B+: ";
    arbol.recorrer();

    return 0;
}

