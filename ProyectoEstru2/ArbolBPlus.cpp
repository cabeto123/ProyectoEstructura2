#include "ArbolBPlus.h"
#include "Inventario.h"
#include "Producto.h"
#include "Clientes.h"


void ArbolBPlus::guardarEnArchivo(const std::string& nombreArchivo) {
	std::ofstream out(nombreArchivo, std::ios::binary);
	if (!out) {
		std::cerr << "Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
		return;
	}

	// Guardar el orden del árbol
	out.write(reinterpret_cast<const char*>(&orden), sizeof(int));

	serializarNodo(out, raiz);

	out.close();
}

void ArbolBPlus::guardarEnArchivoEmpleados(const std::string& nombreArchivo) {
	std::ofstream out(nombreArchivo, std::ios::binary);
	if (!out) {
		std::cerr << "Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
		return;
	}

	// Guardar el orden del árbol
	out.write(reinterpret_cast<const char*>(&orden), sizeof(int));

	serializarNodoEmpleado(out, raiz);

	out.close();
}

void ArbolBPlus::serializarNodo(std::ofstream& out, NodoBPlus* nodo) {
	if (!nodo) return;

	// Guardar si el nodo es hoja
	out.write(reinterpret_cast<const char*>(&nodo->esHoja), sizeof(bool));

	// Guardar el número de claves
	int numClaves = nodo->claves.size();
	out.write(reinterpret_cast<const char*>(&numClaves), sizeof(int));

	// Guardar las claves
	for (const auto& clave : nodo->claves) {
		int tam = clave.size();
		out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
		out.write(clave.c_str(), tam);
	}

	// Guardar los valores (si es un nodo hoja)
	if (nodo->esHoja) {
		for (Producto* prod : nodo->valores) {
			prod->serialize(out); // Asume que Producto tiene un método serialize
		}
	}
	else {
		// Guardar los hijos (si no es un nodo hoja)
		int numHijos = nodo->hijos.size();
		out.write(reinterpret_cast<const char*>(&numHijos), sizeof(int));
		for (NodoBPlus* hijo : nodo->hijos) {
			serializarNodo(out, hijo);
		}
	}

	// Guardar el puntero al siguiente nodo (si es un nodo hoja)
	if (nodo->esHoja) {
		bool tieneSiguiente = (nodo->siguiente != nullptr);
		out.write(reinterpret_cast<const char*>(&tieneSiguiente), sizeof(bool));
		if (tieneSiguiente) {
			serializarNodo(out, nodo->siguiente);
		}
	}
}
void ArbolBPlus::serializarNodoEmpleado(std::ofstream& out, NodoBPlus* nodo) {
	if (!nodo) return;

	// Guardar si el nodo es hoja
	out.write(reinterpret_cast<const char*>(&nodo->esHoja), sizeof(bool));

	// Guardar el número de claves
	int numClaves = nodo->claves.size();
	out.write(reinterpret_cast<const char*>(&numClaves), sizeof(int));

	// Guardar las claves
	for (const auto& clave : nodo->claves) {
		int tam = clave.size();
		out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
		out.write(clave.c_str(), tam);
	}

	// Guardar los valores (si es un nodo hoja)
	if (nodo->esHoja) {
		for (Empleado* prod : nodo->empleados) {
			prod->serialize(out); // Asume que Producto tiene un método serialize
		}
	}
	else {
		// Guardar los hijos (si no es un nodo hoja)
		int numHijos = nodo->hijos.size();
		out.write(reinterpret_cast<const char*>(&numHijos), sizeof(int));
		for (NodoBPlus* hijo : nodo->hijos) {
			serializarNodoEmpleado(out, hijo);
		}
	}

	// Guardar el puntero al siguiente nodo (si es un nodo hoja)
	if (nodo->esHoja) {
		bool tieneSiguiente = (nodo->siguiente != nullptr);
		out.write(reinterpret_cast<const char*>(&tieneSiguiente), sizeof(bool));
		if (tieneSiguiente) {
			serializarNodoEmpleado(out, nodo->siguiente);
		}
	}
}
void ArbolBPlus::cargarDesdeArchivo(const std::string& nombreArchivo) {
	std::ifstream in(nombreArchivo, std::ios::binary);
	if (!in) {
		std::cerr << "Error al abrir el archivo para lectura: " << nombreArchivo << std::endl;
		return;
	}

	// Leer el orden del árbol
	in.read(reinterpret_cast<char*>(&orden), sizeof(int));

	// Deserializar el árbol a partir de la raíz
	raiz = deserializarNodo(in);

	in.close();
}

void ArbolBPlus::cargarDesdeArchivoempleado(const std::string& nombreArchivo) {
	std::ifstream in(nombreArchivo, std::ios::binary);
	if (!in) {
		std::cerr << "Error al abrir el archivo para lectura: " << nombreArchivo << std::endl;
		return;
	}

	// Leer el orden del árbol
	in.read(reinterpret_cast<char*>(&orden), sizeof(int));

	// Deserializar el árbol a partir de la raíz
	raiz = deserializarNodoEmpleado(in);

	in.close();
}


NodoBPlus* ArbolBPlus::deserializarNodo(std::ifstream& in) {
	bool esHoja;
	in.read(reinterpret_cast<char*>(&esHoja), sizeof(bool));
	NodoBPlus* nodo = new NodoBPlus(esHoja);

	// Leer el número de claves
	int numClaves;
	in.read(reinterpret_cast<char*>(&numClaves), sizeof(int));

	// Leer las claves
	for (int i = 0; i < numClaves; i++) {
		int tam;
		in.read(reinterpret_cast<char*>(&tam), sizeof(int));
		std::string clave;
		clave.resize(tam);
		in.read(&clave[0], tam);
		nodo->claves.push_back(clave);
	}

	// Leer los valores (si es un nodo hoja)
	if (esHoja) {
		for (int i = 0; i < numClaves; i++) {
			Producto* prod = Producto::deserialize(in); // Asume que Producto tiene un método deserialize
			nodo->valores.push_back(prod);
		}
	}
	else {
		// Leer los hijos (si no es un nodo hoja)
		int numHijos;
		in.read(reinterpret_cast<char*>(&numHijos), sizeof(int));
		for (int i = 0; i < numHijos; i++) {
			NodoBPlus* hijo = deserializarNodo(in);
			nodo->hijos.push_back(hijo);
		}
	}

	// Leer el puntero al siguiente nodo (si es un nodo hoja)
	if (esHoja) {
		bool tieneSiguiente;
		in.read(reinterpret_cast<char*>(&tieneSiguiente), sizeof(bool));
		if (tieneSiguiente) {
			nodo->siguiente = deserializarNodo(in);
		}
	}

	return nodo;
}
NodoBPlus* ArbolBPlus::deserializarNodoEmpleado(std::ifstream& in)
{
	bool esHoja;
	in.read(reinterpret_cast<char*>(&esHoja), sizeof(bool));
	NodoBPlus* nodo = new NodoBPlus(esHoja);

	// Leer el número de claves
	int numClaves;
	in.read(reinterpret_cast<char*>(&numClaves), sizeof(int));

	// Leer las claves
	for (int i = 0; i < numClaves; i++) {
		int tam;
		in.read(reinterpret_cast<char*>(&tam), sizeof(int));
		std::string clave;
		clave.resize(tam);
		in.read(&clave[0], tam);
		nodo->claves.push_back(clave);
	}

	// Leer los valores (si es un nodo hoja)
	if (esHoja) {
		for (int i = 0; i < numClaves; i++) {
			Empleado* empleado = new Empleado(); // Crear una instancia de Empleado
			empleado->deserialize(in); // Llamar al método de instancia
			nodo->empleados.push_back(empleado); // Agregar el empleado al nodo
		}
	}
	else {
		// Leer los hijos (si no es un nodo hoja)
		int numHijos;
		in.read(reinterpret_cast<char*>(&numHijos), sizeof(int));
		for (int i = 0; i < numHijos; i++) {
			NodoBPlus* hijo = deserializarNodo(in);
			nodo->hijos.push_back(hijo);
		}
	}

	// Leer el puntero al siguiente nodo (si es un nodo hoja)
	if (esHoja) {
		bool tieneSiguiente;
		in.read(reinterpret_cast<char*>(&tieneSiguiente), sizeof(bool));
		if (tieneSiguiente) {
			nodo->siguiente = deserializarNodo(in);
		}
	}

	return nodo;
}
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

void ArbolBPlus::insertar(const std::string& clave, ModuloPadre* m) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	actual->claves.insert(actual->claves.begin() + posicion, clave);

	if (dynamic_cast<Producto*>(m)) {
		Producto* producto = dynamic_cast<Producto*>(m);
		actual->valores.insert(actual->valores.begin() + posicion, producto);
	}
	else if (dynamic_cast<Empleado*>(m)) {
		Empleado* empleado = dynamic_cast<Empleado*>(m);
		actual->empleados.insert(actual->empleados.begin() + posicion, empleado);
	}
	else if (dynamic_cast<Clientes*>(m)) {
		Clientes* cliente = dynamic_cast<Clientes*>(m);
		actual->clientes.insert(actual->clientes.begin() + posicion, cliente);
	}

	if (actual->claves.size() == 2 * orden - 1) {
		dividirHoja(actual);
	}
}

ModuloPadre* ArbolBPlus::buscar(const std::string& clave, ModuloPadre* m) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	if (posicion < actual->claves.size() && actual->claves[posicion] == clave) {
		if (dynamic_cast<Producto*>(m)) {
			return actual->valores[posicion];
		}
		else if (dynamic_cast<Empleado*>(m)) {
			return actual->empleados[posicion];
		}
		else if (dynamic_cast<Clientes*>(m)) {
			return actual->clientes[posicion];
		}
	}
	return nullptr;
}

void ArbolBPlus::recorrer() {
	NodoBPlus* actual = raiz;
	while (!actual->esHoja) {
		actual = actual->hijos[0];
	}

	while (actual != nullptr) {
		for (size_t i = 0; i < actual->claves.size(); ++i) {
			if (!actual->valores.empty()) {
				std::cout << "Clave: " << actual->claves[i] << ", Producto: " << actual->valores[i]->nombre << std::endl;
			}
			else if (!actual->empleados.empty()) {
				std::cout << "Clave: " << actual->claves[i] << ", Empleado: " << actual->empleados[i]->nombre << std::endl;
			}
			else if (!actual->clientes.empty()) {
				std::cout << "Clave: " << actual->claves[i] << ", Cliente: " << actual->clientes[i]->nombre << std::endl;
			}
		}
		actual = actual->siguiente;
	}
}

NodoBPlus* ArbolBPlus::obtenerRaiz() const {
	return raiz;
}
std::vector<Clientes*> ArbolBPlus::buscarClientesConSaldoMayorA(double saldoMinimo) {
	std::vector<Clientes*> clientesEncontrados; // Vector para almacenar los clientes que cumplen la condición
	NodoBPlus* actual = raiz; // Comenzar desde la raíz del árbol

	// Ir al primer nodo hoja
	while (!actual->esHoja) {
		actual = actual->hijos[0];
	}

	// Recorrer todos los nodos hoja
	while (actual != nullptr) {
		// Recorrer las claves y valores del nodo actual
		for (size_t i = 0; i < actual->claves.size(); ++i) {
			// Verificar si el valor es un cliente y si su saldo es mayor al mínimo
			Clientes* cliente = dynamic_cast<Clientes*>(actual->clientes[i]);
			if (cliente && cliente->saldo > saldoMinimo) {
				clientesEncontrados.push_back(cliente); // Agregar al vector de resultados
			}
		}
		// Moverse al siguiente nodo hoja
		actual = actual->siguiente;
	}

	return clientesEncontrados; // Devolver los clientes encontrados
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
	if (!actual->valores.empty()) {
		actual->valores.erase(actual->valores.begin() + posicion);
	}
	else if (!actual->empleados.empty()) {
		actual->empleados.erase(actual->empleados.begin() + posicion);
	}
	else if (!actual->clientes.empty()) {
		actual->clientes.erase(actual->clientes.begin() + posicion);
	}

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
