#pragma once
#include <vector>

#include <string>

using namespace std;
class Pedido {
private: int id;
	   vector < string > productos;
	   string cliente;
	   string fechaEntrega;
	   bool completado;
public: int getId();
	  vector < string > getProductos();
	  string getCliente();
	  string getFechaEntrega();
	  bool estaCompletado();
	  void setEstado(bool estado);
};