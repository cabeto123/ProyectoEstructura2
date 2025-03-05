#pragma once
#include <string>
#include <fstream>
#include "ModuloPadre.h"

using namespace std;

class Venta : public ModuloPadre {
private:
    int idventa;
    int idcliente;
    int productos_vendidos;
    int cantidad;
    double total;
    string fecha_venta;

public:
    // Constructores
    Venta();
    Venta(int idventa, int idcliente, int productos_vendidos, int cantidad, double total, const string& fecha_venta);

    // Getters y setters existentes
    int getIdVenta();
    void setIdVenta(int id);

    int getIdCliente();
    void setIdCliente(int id);

    int getProductosVendidos();
    void setProductosVendidos(int cantidad);

    int getCantidad();
    void setCantidad(int cantidad);

    double getTotal();
    void setTotal(double total);

    string getFechaVenta();
    void setFechaVenta(const string& fecha);

    // Para utilizar con el árbol B+
    string getIdAsString() const;

    // Métodos para serialización
    void serialize(std::ofstream& out) const;
    static Venta* deserialize(std::ifstream& in);
};

