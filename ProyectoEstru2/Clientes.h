#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
#include <vector>
#include <fstream>
#include "ModuloPadre.h"

class Clientes : public ModuloPadre {
public:
    int id; 
    std::string nombre; 
    std::string correo; 
    std::string telefono;
    double saldo; 
    std::vector<std::string> historialCompras; 

    Clientes(); 
    Clientes(int id, const std::string& nombre, const std::string& correo, const std::string& telefono, double saldo); // Constructor con parámetros

    void serialize(std::ofstream& out) const; 
    void deserialize(std::ifstream& in);

    void agregarCompra(const std::string& compra);
    void mostrarInfo() const; 
};

#endif // CLIENTES_H
