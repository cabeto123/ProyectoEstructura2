#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "ModuloPadre.h"

using namespace std;

class Pedido : public ModuloPadre {
private:
    int id;
    vector<string> productos;
    string cliente;
    string fechaEntrega;
    bool completado;

public:
    // Constructor por defecto
    Pedido();

    // Constructor con parámetros
    Pedido(int id, vector<string> productos, string cliente, string fechaEntrega, bool completado = false);

    // Getters y setters existentes
    int getId();
    vector<string> getProductos();
    string getCliente();
    string getFechaEntrega();
    bool estaCompletado();
    void setEstado(bool estado);

    // Para convertir ID a string (necesario para el árbol B+)
    string getIdAsString() const;
    void setId(int id);
    void setProductos(const vector<string>& productos);
    void setCliente(const string& cliente);
    void setFechaEntrega(const string& fecha);

    // Métodos para serialización
    void serialize(std::ofstream& out) const;
    static Pedido* deserialize(std::ifstream& in);
};