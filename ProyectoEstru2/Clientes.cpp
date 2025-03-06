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

void Clientes::agregarCompra(const string& compra) {
    historialCompras.push_back(compra);
}

void Clientes::limpiarHistorialCompras() {
    historialCompras.clear();
}

bool Clientes::SaldoMayorQue(double monto) const {
    return saldo > monto;
}

//implementación de serialize
void Clientes::serialize(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    size_t tamNombre = nombre.size();
    out.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
    out.write(nombre.c_str(), tamNombre);
    size_t tamCorreo = correo.size();
    out.write(reinterpret_cast<const char*>(&tamCorreo), sizeof(tamCorreo));
    out.write(correo.c_str(), tamCorreo);
    size_t tamTelefono = telefono.size();
    out.write(reinterpret_cast<const char*>(&tamTelefono), sizeof(tamTelefono));
    out.write(telefono.c_str(), tamTelefono);
    out.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
}

//implementación de deserialize
void Clientes::deserialize(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    size_t tamNombre;
    in.read(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
    nombre.resize(tamNombre);
    in.read(&nombre[0], tamNombre);
    size_t tamCorreo;
    in.read(reinterpret_cast<char*>(&tamCorreo), sizeof(tamCorreo));
    correo.resize(tamCorreo);
    in.read(&correo[0], tamCorreo);
    size_t tamTelefono;
    in.read(reinterpret_cast<char*>(&tamTelefono), sizeof(tamTelefono));
    telefono.resize(tamTelefono);
    in.read(&telefono[0], tamTelefono);
    in.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));
}
