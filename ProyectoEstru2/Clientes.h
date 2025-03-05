#pragma once

#include <string>
#include <vector>

using namespace std;

class Clientes {
public:
    
    Clientes(int id, const string& nombre, const string& correo, const string& telefono, double saldo);

    int getId() const;
    string getNombre() const;
    string getCorreo() const;
    string getTelefono() const;
    double getSaldo() const;
    const vector<string>& getHistorialCompras() const;


    void setNombre(const string& nombre);
    void setCorreo(const string& correo);
    void setTelefono(const string& telefono);
    void setSaldo(double saldo);

    //Metodo para historial de compras
    void agregarCompra(const string& compra);
    void limpiarHistorialCompras();

    //Metodo para búsqueda compleja
    bool SaldoMayorQue(double monto) const;

private:
    int id;
    string nombre;
    string correo;
    string telefono;
    double saldo;
    vector<string> historialCompras;
};


