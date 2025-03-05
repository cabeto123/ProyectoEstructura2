#pragma once
#include <string>
using namespace std;
class Venta
{
private:
    int idventa;
    int idcliente;
    int productos_vendidos;
    int cantidad;
    double total;
    string fecha_venta;
public:
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

    std::string getFechaVenta();
    void setFechaVenta(const string& fecha);

    // Para utilizar con el árbol B+
   string getIdAsString() const;

    // Métodos para serialización
   void serialize(std::ofstream& out) const;
   static Venta* deserialize(std::ifstream& in);
};

