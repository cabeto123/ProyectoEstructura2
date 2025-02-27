#include "ArbolBPlus.h"
#include "Inventario.h"
#include "Producto.h"

void ArbolBPlus::guardarEnArchivo(const std::string& nombreArchivo) {
	std::ofstream out(nombreArchivo, std::ios::binary);
	if (!out) {
		std::cerr << "Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
		return;
	}

	// Guardar el orden del �rbol
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

	// Guardar el orden del �rbol
	out.write(reinterpret_cast<const char*>(&orden), sizeof(int));

	serializarNodoEmpleado(out, raiz);

	out.close();
}

void ArbolBPlus::serializarNodo(std::ofstream& out, NodoBPlus* nodo) {
	if (!nodo) return;

	// Guardar si el nodo es hoja
	out.write(reinterpret_cast<const char*>(&nodo->esHoja), sizeof(bool));

	// Guardar el n�mero de claves
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
			prod->serialize(out); // Asume que Producto tiene un m�todo serialize
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

	// Guardar el n�mero de claves
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
			prod->serialize(out); // Asume que Producto tiene un m�todo serialize
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

	// Leer el orden del �rbol
	in.read(reinterpret_cast<char*>(&orden), sizeof(int));

	// Deserializar el �rbol a partir de la ra�z
	raiz = deserializarNodo(in);

	in.close();
}

void ArbolBPlus::cargarDesdeArchivoempleado(const std::string& nombreArchivo) {
	std::ifstream in(nombreArchivo, std::ios::binary);
	if (!in) {
		std::cerr << "Error al abrir el archivo para lectura: " << nombreArchivo << std::endl;
		return;
	}

	// Leer el orden del �rbol
	in.read(reinterpret_cast<char*>(&orden), sizeof(int));

	// Deserializar el �rbol a partir de la ra�z
	raiz = deserializarNodoEmpleado(in);

	in.close();
}


NodoBPlus* ArbolBPlus::deserializarNodo(std::ifstream& in) {
	bool esHoja;
	in.read(reinterpret_cast<char*>(&esHoja), sizeof(bool));
	NodoBPlus* nodo = new NodoBPlus(esHoja);

	// Leer el n�mero de claves
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
			Producto* prod = Producto::deserialize(in); // Asume que Producto tiene un m�todo deserialize
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

	// Leer el n�mero de claves
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
			empleado->deserialize(in); // Llamar al m�todo de instancia
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
NodoBPlus* ArbolBPlus::deserializarNodoCliente(std::ifstream& in)
{
	return nullptr;
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

void ArbolBPlus::insertar(const std::string& clave, Producto* producto) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	actual->claves.insert(actual->claves.begin() + posicion, clave);
	actual->valores.insert(actual->valores.begin() + posicion, producto);

	if (actual->claves.size() == 2 * orden - 1) {
		dividirHoja(actual);
	}
}

void ArbolBPlus::insertarempleado(const std::string& clave, Empleado* empleado)
{
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	actual->claves.insert(actual->claves.begin() + posicion, clave);
	actual->empleados.insert(actual->empleados.begin() + posicion, empleado);

	if (actual->claves.size() == 2 * orden - 1) {
		dividirHoja(actual);
	}
}

Producto* ArbolBPlus::buscar(const std::string& clave) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	if (posicion < actual->claves.size() && actual->claves[posicion] == clave) {
		return actual->valores[posicion];
	}
	return nullptr;
}
Empleado* ArbolBPlus::buscarempleado(const std::string& clave) {
	NodoBPlus* actual = raiz;

	while (!actual->esHoja) {
		auto posicion = upper_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
		actual = actual->hijos[posicion];
	}

	auto posicion = lower_bound(actual->claves.begin(), actual->claves.end(), clave) - actual->claves.begin();
	if (posicion < actual->claves.size() && actual->claves[posicion] == clave) {
		return actual->empleados[posicion];
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
			std::cout << "Clave: " << actual->claves[i] << ", Producto: " << actual->valores[i]->nombre << std::endl;

		}
		actual = actual->siguiente;
	}
}
