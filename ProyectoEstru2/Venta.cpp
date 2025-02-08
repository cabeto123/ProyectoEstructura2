#include "Venta.h"
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

void Venta::setFechaVenta(const std::string& fecha) {
    fecha_venta = fecha;
}