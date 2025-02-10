#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <vector>
#include <fstream>
#include "ArbolBPlus.h"

class Inventario {
public:
	ArbolBPlus arbolPorId;
	ArbolBPlus arbolPorCategoria;
	std::string id;
	std::string nombre;
	std::string categoria;
	double precio;
	int cantidad;
	bool disponible;

public:
	Inventario() : arbolPorId(3), arbolPorCategoria(3) {}
	void agregarProducto(Producto* producto);
	Producto* buscarPorId(std::string id);
	std::vector<Producto*> buscarPorCategoria(std::string categoria);
	void recorrerInventario();
	void guardarEnArchivoBinario(const std::string& nombreArchivo);
	void escribirCadenaBinario(std::ofstream& archivo, const std::string& cadena);
};

#endif // INVENTARIO_H