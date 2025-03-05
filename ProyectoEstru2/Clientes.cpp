#include "Clientes.h"
#include <algorithm>

using namespace std;

Clientes::Clientes(int id, const string& nombre, const string& correo, const string& telefono, double saldo)
    : id(id), nombre(nombre), correo(correo), telefono(telefono), saldo(saldo) {
}

int Clientes::getId() const {
    return id;
}

string Clientes::getNombre() const {
    return nombre;
}

string Clientes::getCorreo() const {
    return correo;
}

string Clientes::getTelefono() const {
    return telefono;
}

double Clientes::getSaldo() const {
    return saldo;
}

const vector<string>& Clientes::getHistorialCompras() const {
    return historialCompras;
}


void Clientes::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Clientes::setCorreo(const string& correo) {
    this->correo = correo;
}

void Clientes::setTelefono(const string& telefono) {
    this->telefono = telefono;
}

void Clientes::setSaldo(double saldo) {
    this->saldo = saldo;
}

// Metodo para historial de compras
void Clientes::agregarCompra(const string& compra) {
    historialCompras.push_back(compra);
}

void Clientes::limpiarHistorialCompras() {
    historialCompras.clear();
}

// Metodo para busqueda compleja
bool Clientes::SaldoMayorQue(double monto) const {
    return saldo > monto;
}
