#include "Venta.h"
#include <iostream>

Venta::Venta() : idventa(0), idcliente(0), productos_vendidos(0), cantidad(0), total(0.0) {
}

Venta::Venta(int idventa, int idcliente, int productos_vendidos, int cantidad, double total, const string& fecha_venta)
    : idventa(idventa), idcliente(idcliente), productos_vendidos(productos_vendidos),
    cantidad(cantidad), total(total), fecha_venta(fecha_venta) {
}

int Venta::getIdVenta() {
    return idventa;
}

void Venta::setIdVenta(int id) {
    idventa = id;
}

int Venta::getIdCliente() {
    return idcliente;
}

void Venta::setIdCliente(int id) {
    idcliente = id;
}

int Venta::getProductosVendidos() {
    return productos_vendidos;
}

void Venta::setProductosVendidos(int cantidad) {
    productos_vendidos = cantidad;
}

int Venta::getCantidad() {
    return cantidad;
}

void Venta::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

double Venta::getTotal() {
    return total;
}

void Venta::setTotal(double total) {
    this->total = total;
}

string Venta::getFechaVenta() {
    return fecha_venta;
}

void Venta::setFechaVenta(const string& fecha) {
    fecha_venta = fecha;
}

string Venta::getIdAsString() const {
    return to_string(idventa);
}

void Venta::serialize(std::ofstream& out) const {
    // Escribir IDs
    out.write(reinterpret_cast<const char*>(&idventa), sizeof(int));
    out.write(reinterpret_cast<const char*>(&idcliente), sizeof(int));

    // Escribir productos vendidos y cantidad
    out.write(reinterpret_cast<const char*>(&productos_vendidos), sizeof(int));
    out.write(reinterpret_cast<const char*>(&cantidad), sizeof(int));

    // Escribir total
    out.write(reinterpret_cast<const char*>(&total), sizeof(double));

    // Escribir fecha de venta
    int fechaSize = fecha_venta.size();
    out.write(reinterpret_cast<const char*>(&fechaSize), sizeof(int));
    out.write(fecha_venta.c_str(), fechaSize);
}

Venta* Venta::deserialize(std::ifstream& in) {
    Venta* v = new Venta();

    // Leer IDs
    in.read(reinterpret_cast<char*>(&v->idventa), sizeof(int));
    in.read(reinterpret_cast<char*>(&v->idcliente), sizeof(int));

    // Leer productos vendidos y cantidad
    in.read(reinterpret_cast<char*>(&v->productos_vendidos), sizeof(int));
    in.read(reinterpret_cast<char*>(&v->cantidad), sizeof(int));

    // Leer total
    in.read(reinterpret_cast<char*>(&v->total), sizeof(double));

    // Leer fecha de venta
    int fechaSize;
    in.read(reinterpret_cast<char*>(&fechaSize), sizeof(int));
    v->fecha_venta.resize(fechaSize);
    in.read(&v->fecha_venta[0], fechaSize);

    return v;
}