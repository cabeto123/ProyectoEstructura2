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

public:
	Inventario() : arbolPorId(3), arbolPorCategoria(3) {}
	void agregarProducto(Producto* producto);
	Producto* buscarPorId(std::string id);
	std::vector<Producto*> buscarPorCategoria(std::string categoria);
	void recorrerInventario();
};

#endif // INVENTARIO_H