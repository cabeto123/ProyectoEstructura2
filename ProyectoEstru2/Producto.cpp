#include "Producto.h"




void Producto::serialize(std::ofstream& out)const {
	int tam = id.size();
	out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
	out.write(id.c_str(), tam);

	tam = nombre.size();
	out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
	out.write(nombre.c_str(), tam);

	tam = categoria.size();
	out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
	out.write(categoria.c_str(), tam);

	out.write(reinterpret_cast<const char*>(&precio), sizeof(double));
	out.write(reinterpret_cast<const char*>(&cantidad), sizeof(int));
	out.write(reinterpret_cast<const char*>(&disponible), sizeof(bool));
}

Producto* Producto::deserialize(std::ifstream& in) {
	Producto* p = new Producto();
	int tam = 0;

	// Deserializar 'id'
	in.read(reinterpret_cast<char*>(&tam), sizeof(int));
	p->id.resize(tam);
	in.read(&p->id[0], tam);

	// Deserializar 'nombre'
	in.read(reinterpret_cast<char*>(&tam), sizeof(int));
	p->nombre.resize(tam);
	in.read(&p->nombre[0], tam);

	// Deserializar 'categoria'
	in.read(reinterpret_cast<char*>(&tam), sizeof(int));
	p->categoria.resize(tam);
	in.read(&p->categoria[0], tam);

	// Deserializar 'precio'
	in.read(reinterpret_cast<char*>(&p->precio), sizeof(double));

	// Deserializar 'cantidad'
	in.read(reinterpret_cast<char*>(&p->cantidad), sizeof(int));

	// Deserializar 'disponible'
	in.read(reinterpret_cast<char*>(&p->disponible), sizeof(bool));

	return p;
}



Producto::Producto(std::string id, std::string nombre, std::string categoria, double precio, int cantidad, bool disponible)
{
}

Producto::Producto()
{
}




