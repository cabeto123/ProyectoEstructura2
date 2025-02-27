#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
#include <vector>
#include <fstream>
#include "ModuloPadre.h" // Incluye la clase base ModuloPadre

class Clientes : public ModuloPadre {
public:
    int id; // ID del cliente
    std::string nombre; // Nombre del cliente
    std::string correo; // Correo electrónico del cliente
    std::string telefono; // Teléfono del cliente
    double saldo; // Saldo del cliente
    std::vector<std::string> historialCompras; // Historial de compras del cliente

    // Constructores
    Clientes(); // Constructor por defecto
    Clientes(int id, const std::string& nombre, const std::string& correo, const std::string& telefono, double saldo); // Constructor con parámetros

    // Métodos de serialización y deserialización
    void serialize(std::ofstream& out) const; // Guarda los datos del cliente en un archivo binario
    void deserialize(std::ifstream& in); // Carga los datos del cliente desde un archivo binario

    // Métodos adicionales (opcionales)
    void agregarCompra(const std::string& compra); // Agrega una compra al historial
    void mostrarInfo() const; // Muestra la información del cliente
};

#endif // CLIENTES_H
