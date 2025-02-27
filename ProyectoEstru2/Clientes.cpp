#include "Clientes.h"
#include <iostream>

// Implementación del constructor por defecto
Clientes::Clientes() : id(0), saldo(0) {}

// Implementación del constructor con parámetros
Clientes::Clientes(int id, const std::string& nombre, const std::string& correo, const std::string& telefono, double saldo)
    : id(id), nombre(nombre), correo(correo), telefono(telefono), saldo(saldo) {
}

// Implementación del método serialize
void Clientes::serialize(std::ofstream& out) const {
    // Guardar el ID
    out.write(reinterpret_cast<const char*>(&id), sizeof(int));

    // Guardar el nombre
    int tam = nombre.size();
    out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
    out.write(nombre.c_str(), tam);

    // Guardar el correo
    tam = correo.size();
    out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
    out.write(correo.c_str(), tam);

    // Guardar el teléfono
    tam = telefono.size();
    out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
    out.write(telefono.c_str(), tam);

    // Guardar el saldo
    out.write(reinterpret_cast<const char*>(&saldo), sizeof(double));

    // Guardar el historial de compras
    int numCompras = historialCompras.size();
    out.write(reinterpret_cast<const char*>(&numCompras), sizeof(int));
    for (const std::string& compra : historialCompras) {
        tam = compra.size();
        out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
        out.write(compra.c_str(), tam);
    }
}

// Implementación del método deserialize
void Clientes::deserialize(std::ifstream& in) {
    // Leer el ID
    in.read(reinterpret_cast<char*>(&id), sizeof(int));

    // Leer el nombre
    int tam;
    in.read(reinterpret_cast<char*>(&tam), sizeof(int));
    nombre.resize(tam);
    in.read(&nombre[0], tam);

    // Leer el correo
    in.read(reinterpret_cast<char*>(&tam), sizeof(int));
    correo.resize(tam);
    in.read(&correo[0], tam);

    // Leer el teléfono
    in.read(reinterpret_cast<char*>(&tam), sizeof(int));
    telefono.resize(tam);
    in.read(&telefono[0], tam);

    // Leer el saldo
    in.read(reinterpret_cast<char*>(&saldo), sizeof(double));

    // Leer el historial de compras
    int numCompras;
    in.read(reinterpret_cast<char*>(&numCompras), sizeof(int));
    historialCompras.clear();
    for (int i = 0; i < numCompras; ++i) {
        in.read(reinterpret_cast<char*>(&tam), sizeof(int));
        std::string compra;
        compra.resize(tam);
        in.read(&compra[0], tam);
        historialCompras.push_back(compra);
    }
}

// Implementación del método agregarCompra
void Clientes::agregarCompra(const std::string& compra) {
    historialCompras.push_back(compra);
}

// Implementación del método mostrarInfo
void Clientes::mostrarInfo() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Correo: " << correo << std::endl;
    std::cout << "Teléfono: " << telefono << std::endl;
    std::cout << "Saldo: " << saldo << std::endl;
    std::cout << "Historial de compras: ";
    for (const std::string& compra : historialCompras) {
        std::cout << compra << " ";
    }
    std::cout << std::endl;
}