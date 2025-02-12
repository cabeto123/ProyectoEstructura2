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
