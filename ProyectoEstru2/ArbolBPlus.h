#pragma once
#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Producto.h"
#include "Empleado.h"
#include <type_traits> // Para std::is_same

class NodoBPlus {
public:
	bool esHoja;
	std::vector<std::string> claves;
	std::vector<Producto*> valores;
	std::vector<Empleado*> empleados;
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
	ArbolBPlus();
	ArbolBPlus(int _orden) : orden(_orden), raiz(new NodoBPlus(true)) {}
	void insertar(const std::string& clave, Producto* producto);
	void insertarempleado(const std::string& clave, Empleado* empleado);
	Producto* buscar(const std::string& clave);
	Empleado* buscarempleado(const std::string& clave);
	void recorrer();
	NodoBPlus* obtenerRaiz() const;
	template <typename T>
	void guardarEnArchivo(const T* dato, const std::string& nombreArchivo) {
		std::ofstream out(nombreArchivo, std::ios::binary);
		if (!out) {
			std::cerr << "Error al abrir el archivo para escritura: " << nombreArchivo << std::endl;
			return;
		}

		// Guardar el orden del árbol
		out.write(reinterpret_cast<const char*>(&orden), sizeof(int));

		serializarNodo(dato, out, raiz);

		out.close();
	}
	template <typename T>
	void cargarDesdeArchivo(T* dato, const std::string& nombreArchivo) {
		std::ifstream in(nombreArchivo, std::ios::binary);
		if (!in) {
			std::cerr << "Error al abrir el archivo para lectura: " << nombreArchivo << std::endl;
			return;
		}

		// Leer el orden del árbol
		in.read(reinterpret_cast<char*>(&orden), sizeof(int));

		// Deserializar el árbol a partir de la raíz
		raiz = deserializarNodo(dato,in);

		in.close();
	}
	template <typename T>
	void serializarNodo(const T* dato, std::ofstream& out, NodoBPlus* nodo) 
	{
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
			
			if constexpr (std::is_same<T, Empleado>::value)
			{
				for (Empleado* prod : nodo->empleados) {
					prod->serialize(out); // Asume que Producto tiene un método serialize
				}
			}
			
			if constexpr (std::is_same<T, Producto>::value)
			{
				for (Producto* prod : nodo->valores) {
					prod->serialize(out); // Asume que Producto tiene un método serialize
				}
			}

		}
		else {
			// Guardar los hijos (si no es un nodo hoja)
			int numHijos = nodo->hijos.size();
			out.write(reinterpret_cast<const char*>(&numHijos), sizeof(int));
			for (NodoBPlus* hijo : nodo->hijos) {
				serializarNodo(dato,out, hijo);
			}
		}

		// Guardar el puntero al siguiente nodo (si es un nodo hoja)
		if (nodo->esHoja) {
			bool tieneSiguiente = (nodo->siguiente != nullptr);
			out.write(reinterpret_cast<const char*>(&tieneSiguiente), sizeof(bool));
			if (tieneSiguiente) {
				serializarNodo(dato,out, nodo->siguiente);
			}
		}
	}
	template <typename T>
	NodoBPlus* deserializarNodo(const T* dato, std::ifstream& in) {
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
			if constexpr (std::is_same<T, Empleado>::value)
			{
				for (int i = 0; i < numClaves; i++) {
					Empleado* empleado = new Empleado(); // Crear una instancia de Empleado
					empleado->deserialize(in); // Llamar al método de instancia
					nodo->empleados.push_back(empleado); // Agregar el empleado al nodo
				}
			}
			if constexpr (std::is_same<T, Producto>::value)
			{
				for (int i = 0; i < numClaves; i++) {
					Producto* prod = Producto::deserialize(in); // Asume que Producto tiene un método deserialize
					nodo->valores.push_back(prod);
				}
			}

		}
		else {
			// Leer los hijos (si no es un nodo hoja)
			int numHijos;
			in.read(reinterpret_cast<char*>(&numHijos), sizeof(int));
			for (int i = 0; i < numHijos; i++) {
				NodoBPlus* hijo = deserializarNodo(dato,in);
				nodo->hijos.push_back(hijo);
			}
		}

		// Leer el puntero al siguiente nodo (si es un nodo hoja)
		if (esHoja) {
			bool tieneSiguiente;
			in.read(reinterpret_cast<char*>(&tieneSiguiente), sizeof(bool));
			if (tieneSiguiente) {
				nodo->siguiente = deserializarNodo(dato,in);
			}
		}

		return nodo;
	}
};

#endif // ARBOLBPLUS_H