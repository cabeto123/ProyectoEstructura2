#include "Inventario.h"
void Inventario::agregarProducto(Producto* producto) {
    arbolPorId.insertar(producto->id, producto);
    arbolPorCategoria.insertar(producto->categoria, producto);
}

Producto* Inventario::buscarPorId(std::string id) {
    Producto* p=reinterpret_cast<Producto*> (arbolPorId.buscar(id,new Producto()));
    return p;
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

void Inventario::guardarEnArchivoBinario(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << " para escritura.\n";
        return;
    }

    NodoBPlus* nodoActual = arbolPorId.obtenerRaiz(); 
    if (!nodoActual) {
        std::cerr << "El árbol está vacío, no hay nada que guardar.\n";
        archivo.close();
        return;
    }

    // Desplázate al nodo hoja más a la izquierda
    while (!nodoActual->esHoja) {
        nodoActual = nodoActual->hijos[0];
    }

    while (nodoActual) {
        for (size_t i = 0; i < nodoActual->claves.size(); ++i) {
            Producto* producto = nodoActual->valores[i];
            if (producto) {
                // Escribir el producto en el archivo binario
                archivo.write(reinterpret_cast<const char*>(&producto->precio), sizeof(producto->precio));
                archivo.write(reinterpret_cast<const char*>(&producto->cantidad), sizeof(producto->cantidad));

                // Guardar cadenas con su longitud
                escribirCadenaBinario(archivo, producto->id);
                escribirCadenaBinario(archivo, producto->nombre);
                escribirCadenaBinario(archivo, producto->categoria);

                archivo.write(reinterpret_cast<const char*>(&producto->disponible), sizeof(producto->disponible));
            }
        }
        nodoActual = nodoActual->siguiente;
    }

    archivo.close();
    std::cout << "Inventario guardado correctamente en el archivo " << nombreArchivo << "\n";
}

void Inventario::escribirCadenaBinario(std::ofstream& archivo, const std::string& cadena) {
    size_t longitud = cadena.size();
    archivo.write(reinterpret_cast<const char*>(&longitud), sizeof(longitud));
    archivo.write(cadena.c_str(), longitud);
}