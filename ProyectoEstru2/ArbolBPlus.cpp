#include "ArbolBPlus.h"
#include "Inventario.h"
#include "Producto.h"

void ArbolBPlus::insertarEnNodoInterno(const std::string& clave, NodoBPlus* nodo, NodoBPlus* hijoDerecho) {
	auto posicion = upper_bound(nodo->claves.begin(), nodo->claves.end(), clave) - nodo->claves.begin();
	nodo->claves.insert(nodo->claves.begin() + posicion, clave);
	nodo->hijos.insert(nodo->hijos.begin() + posicion + 1, hijoDerecho);

	if (nodo->claves.size() == 2 * orden - 1) {
		dividirNodoInterno(nodo);
	}
}

void ArbolBPlus::dividirNodoInterno(NodoBPlus* nodo) {
	int mitad = nodo->claves.size() / 2;
	std::string clavePromocionada = nodo->claves[mitad];

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
	nodoDerecho->valores.assign(nodo->valores.begin() + mitad, nodo->valores.end());
	nodo->claves.resize(mitad);
	nodo->valores.resize(mitad);

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

void ArbolBPlus::insertar(const std::string& clave,ModuloPadre* m) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	actual->claves.insert(actual->claves.begin() + posicion, clave);
	if (dynamic_cast<Producto*>(m))
	{
		Producto* producto = dynamic_cast<Producto*>(m);
		actual->valores.insert(actual->valores.begin() + posicion, producto);
	}
	if (dynamic_cast<Empleado*>(m))
	{
		Empleado* empleado = dynamic_cast<Empleado*>(m);
		actual->empleados.insert(actual->empleados.begin() + posicion, empleado);

	}


	if (actual->claves.size() == 2 * orden - 1) {
		dividirHoja(actual);
	}
}

//void ArbolBPlus::insertarempleado(const std::string& clave, Empleado* empleado)
//{
//	NodoBPlus* actual = raiz;
//
//	while (!actual->esHoja) {
//		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
//		actual = actual->hijos[posicion];
//	}
//
//	auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
//	actual->claves.insert(actual->claves.begin() + posicion, clave);
//
//	if (actual->claves.size() == 2 * orden - 1) {
//		dividirHoja(actual);
//	}
//}

ModuloPadre* ArbolBPlus::buscar(const std::string& clave,ModuloPadre* m) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	if (posicion < actual->claves.size() && actual->claves[posicion] == clave) {
		Producto* z = reinterpret_cast<Producto*>(m);
		if (typeid(*z) == typeid(Producto))
		{
			return actual->valores[posicion];
		}
		Empleado* x = reinterpret_cast<Empleado*>(m);
		if (typeid(*x) == typeid(Empleado))
		{
			return actual->empleados[posicion];
		}
	}
	return nullptr;
}
//Empleado* ArbolBPlus::buscarempleado(const std::string& clave) {
//	NodoBPlus* actual = raiz;
//
//	while (!actual->esHoja) {
//		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
//		actual = actual->hijos[posicion];
//	}
//
//	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
//	if (posicion < actual->claves.size() && actual->claves[posicion] == clave) {
//		return actual->empleados[posicion];
//	}
//	return nullptr;
//}

void ArbolBPlus::recorrer() {
	NodoBPlus* actual = raiz;
	while (!actual->esHoja) {
		actual = actual->hijos[0];
	}

	while (actual != nullptr) {
		for (size_t i = 0; i < actual->claves.size(); ++i) {
			std::cout << "Clave: " << actual->claves[i] << ", Producto: " << actual->valores[i]->nombre << std::endl;

		}
		actual = actual->siguiente;
	}
}

NodoBPlus* ArbolBPlus::obtenerRaiz() const {
	return raiz;
}

void ArbolBPlus::eliminar(const std::string& clave) {
	NodoBPlus* actual = raiz;
	NodoBPlus* padre = nullptr;
	int indicePadre = -1;

	while (!actual->esHoja) {
		auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		padre = actual;
		indicePadre = posicion;
		actual = actual->hijos[posicion];
	}

	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	if (posicion >= actual->claves.size() || actual->claves[posicion] != clave) {
		std::cout << "Clave no encontrada." << std::endl;
		return;
	}

	actual->claves.erase(actual->claves.begin() + posicion);
	actual->valores.erase(actual->valores.begin() + posicion);
	if (actual->claves.size() >= orden / 2 || actual == raiz) return;
	reequilibrarDespuesDeEliminar(actual, padre, indicePadre);
}


void ArbolBPlus::reequilibrarDespuesDeEliminar(NodoBPlus* nodo, NodoBPlus* padre, int indicePadre) {
	if (!padre) return;

	NodoBPlus* hermanoIzquierdo = (indicePadre > 0) ? padre->hijos[indicePadre - 1] : nullptr;
	NodoBPlus* hermanoDerecho = (indicePadre < padre->hijos.size() - 1) ? padre->hijos[indicePadre + 1] : nullptr;

	if (hermanoIzquierdo && hermanoIzquierdo->claves.size() > orden / 2) {
		nodo->claves.insert(nodo->claves.begin(), hermanoIzquierdo->claves.back());
		nodo->valores.insert(nodo->valores.begin(), hermanoIzquierdo->valores.back());
		hermanoIzquierdo->claves.pop_back();
		hermanoIzquierdo->valores.pop_back();
		padre->claves[indicePadre - 1] = nodo->claves[0];
		return;
	}

	if (hermanoDerecho && hermanoDerecho->claves.size() > orden / 2) {
		nodo->claves.push_back(hermanoDerecho->claves.front());
		nodo->valores.push_back(hermanoDerecho->valores.front());
		hermanoDerecho->claves.erase(hermanoDerecho->claves.begin());
		hermanoDerecho->valores.erase(hermanoDerecho->valores.begin());
		padre->claves[indicePadre] = hermanoDerecho->claves[0];
		return;
	}

	if (hermanoIzquierdo) {
		hermanoIzquierdo->claves.insert(hermanoIzquierdo->claves.end(), nodo->claves.begin(), nodo->claves.end());
		hermanoIzquierdo->valores.insert(hermanoIzquierdo->valores.end(), nodo->valores.begin(), nodo->valores.end());
		hermanoIzquierdo->siguiente = nodo->siguiente;
		padre->claves.erase(padre->claves.begin() + indicePadre - 1);
		padre->hijos.erase(padre->hijos.begin() + indicePadre);
		delete nodo;
	}
	else if (hermanoDerecho) {
		nodo->claves.insert(nodo->claves.end(), hermanoDerecho->claves.begin(), hermanoDerecho->claves.end());
		nodo->valores.insert(nodo->valores.end(), hermanoDerecho->valores.begin(), hermanoDerecho->valores.end());
		nodo->siguiente = hermanoDerecho->siguiente;
		padre->claves.erase(padre->claves.begin() + indicePadre);
		padre->hijos.erase(padre->hijos.begin() + indicePadre + 1);
		delete hermanoDerecho;
	}

	if (padre == raiz && padre->claves.empty()) {
		raiz = padre->hijos[0];
		delete padre;
	}
}
