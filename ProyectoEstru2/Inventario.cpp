#include "Inventario.h"

Producto::Producto(std::string id, std::string nombre, std::string categoria, double precio, int cantidad, bool disponible)
    : id(id), nombre(nombre), categoria(categoria), precio(precio), cantidad(cantidad), disponible(disponible) {
}

void Inventario::agregarProducto(Producto* producto) {
    arbolPorId.insertar(producto->id, producto);
    arbolPorCategoria.insertar(producto->categoria, producto);
}

Producto* Inventario::buscarPorId(std::string id) {
    return arbolPorId.buscar(id);
}

std::vector<Producto*> Inventario::buscarPorCategoria(std::string categoria) {
    std::vector<Producto*> productos;
    return productos;
}

void Inventario::recorrerInventario() {
    std::cout << "Recorriendo inventario por ID:" << std::endl;
    arbolPorId.recorrer();

    std::cout << "Recorriendo inventario por categoría:" << std::endl;
    arbolPorCategoria.recorrer();
}