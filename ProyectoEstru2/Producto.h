#pragma once
#include <fstream>
#include <string>
#include "ModuloPadre.h"

using namespace std;
class Producto:public ModuloPadre
{
public:
	std::string id;
	std::string nombre;
	std::string categoria;
	double precio;
	int cantidad;
	bool disponible;

	// Producto.cpp
	
	void serialize(std::ofstream& out) const ;
	static   Producto* deserialize(std::ifstream& in);

	Producto(std::string id, std::string nombre, std::string categoria, double precio, int cantidad, bool disponible);
	Producto();
	
};

