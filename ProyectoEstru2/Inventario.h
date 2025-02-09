#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <vector>
#include "ArbolBPlus.h"

class Producto {
public:
    std::string id;
    std::string nombre;
    std::string categoria;
    double precio;
    int cantidad;
    bool disponible;

    Producto(std::string id, std::string nombre, std::string categoria, double precio, int cantidad, bool disponible);
};

class Inventario {
private:
    ArbolBPlus arbolPorId;
    ArbolBPlus arbolPorCategoria;

public:
    Inventario() : arbolPorId(3), arbolPorCategoria(3) {}
    void agregarProducto(Producto* producto);
    Producto* buscarPorId(std::string id);
    std::vector<Producto*> buscarPorCategoria(std::string categoria);
    void recorrerInventario();
};

#endif // INVENTARIO_H