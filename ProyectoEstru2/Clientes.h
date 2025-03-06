#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "ModuloPadre.h" 

using namespace std;

class Clientes : public ModuloPadre {
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

    void agregarCompra(const string& compra);
    void limpiarHistorialCompras();

    bool SaldoMayorQue(double monto) const;

    void serialize(std::ofstream& out) const;  
    void deserialize(std::ifstream& in); 

private:
    int id;
    string nombre;
    string correo;
    string telefono;
    double saldo;
    vector<string> historialCompras;
};

