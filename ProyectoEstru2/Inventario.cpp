#include "Inventario.h"
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