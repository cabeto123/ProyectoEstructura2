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

class NodoBPlus {
public:
	bool esHoja;
	std::vector<std::string> claves;
	std::vector<Producto*> valores;
	std::vector<Empleado*> empleados;
	std::vector<Clientes*> clientes;
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
	NodoBPlus* deserializarNodo(std::ifstream& in);
	NodoBPlus* deserializarNodoEmpleado(std::ifstream& in);
	NodoBPlus* deserializarNodoCliente(std::ifstream& in); 
	void serializarNodo(std::ofstream& out, NodoBPlus* nodo);
	void serializarNodoEmpleado(std::ofstream& out, NodoBPlus* nodo);
public:
	ArbolBPlus();
	ArbolBPlus(int _orden) : orden(_orden), raiz(new NodoBPlus(true)) {}
	void cargarDesdeArchivo(const std::string& nombreArchivo);
	void cargarDesdeArchivoempleado(const std::string& nombreArchivo);
	void guardarEnArchivo(const std::string& nombreArchivo);
	void guardarEnArchivoEmpleados(const std::string& nombreArchivo);
	void insertar(const std::string& clave, Producto* producto);
	void insertarempleado(const std::string& clave, Empleado* empleado);
	Producto* buscar(const std::string& clave);
	Empleado* buscarempleado(const std::string& clave);
	void recorrer();
};

#endif // ARBOLBPLUS_H