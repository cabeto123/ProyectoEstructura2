#include "Pedido.h"
#include <iostream>

Pedido::Pedido() : id(0), completado(false) {
}

Pedido::Pedido(int id, vector<string> productos, string cliente, string fechaEntrega, bool completado)
    : id(id), productos(productos), cliente(cliente), fechaEntrega(fechaEntrega), completado(completado) {
}

int Pedido::getId() {
    return id;
}

vector<string> Pedido::getProductos() {
    return productos;
}

string Pedido::getCliente() {
    return cliente;
}

string Pedido::getFechaEntrega() {
    return fechaEntrega;
}

bool Pedido::estaCompletado() {
    return completado;
}

void Pedido::setEstado(bool estado) {
    completado = estado;
}

string Pedido::getIdAsString() const {
    return to_string(id);
}

void Pedido::setId(int newId) {
    id = newId;
}

void Pedido::setProductos(const vector<string>& newProductos) {
    productos = newProductos;
}

void Pedido::setCliente(const string& newCliente) {
    cliente = newCliente;
}

void Pedido::setFechaEntrega(const string& fecha) {
    fechaEntrega = fecha;
}

void Pedido::serialize(std::ofstream& out) const {
    // Escribir ID
    out.write(reinterpret_cast<const char*>(&id), sizeof(int));

    // Escribir productos
    int numProductos = productos.size();
    out.write(reinterpret_cast<const char*>(&numProductos), sizeof(int));

    for (const auto& producto : productos) {
        int tam = producto.size();
        out.write(reinterpret_cast<const char*>(&tam), sizeof(int));
        out.write(producto.c_str(), tam);
    }

    // Escribir cliente
    int clienteSize = cliente.size();
    out.write(reinterpret_cast<const char*>(&clienteSize), sizeof(int));
    out.write(cliente.c_str(), clienteSize);

    // Escribir fecha de entrega
    int fechaSize = fechaEntrega.size();
    out.write(reinterpret_cast<const char*>(&fechaSize), sizeof(int));
    out.write(fechaEntrega.c_str(), fechaSize);

    // Escribir estado de completado
    out.write(reinterpret_cast<const char*>(&completado), sizeof(bool));
}

Pedido* Pedido::deserialize(std::ifstream& in) {
    Pedido* p = new Pedido();

    // Leer ID
    in.read(reinterpret_cast<char*>(&p->id), sizeof(int));

    // Leer productos
    int numProductos;
    in.read(reinterpret_cast<char*>(&numProductos), sizeof(int));

    for (int i = 0; i < numProductos; i++) {
        int tam;
        in.read(reinterpret_cast<char*>(&tam), sizeof(int));
        string producto;
        producto.resize(tam);
        in.read(&producto[0], tam);
        p->productos.push_back(producto);
    }

    // Leer cliente
    int clienteSize;
    in.read(reinterpret_cast<char*>(&clienteSize), sizeof(int));
    p->cliente.resize(clienteSize);
    in.read(&p->cliente[0], clienteSize);

    // Leer fecha de entrega
    int fechaSize;
    in.read(reinterpret_cast<char*>(&fechaSize), sizeof(int));
    p->fechaEntrega.resize(fechaSize);
    in.read(&p->fechaEntrega[0], fechaSize);

    // Leer estado de completado
    in.read(reinterpret_cast<char*>(&p->completado), sizeof(bool));

    return p;
}