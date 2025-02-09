#pragma once
#include <fstream>
#include <string>
using namespace std;
class Producto
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

