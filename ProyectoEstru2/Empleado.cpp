#include "Empleado.h"
#include <fstream>
#include <string>
Empleado::Empleado(string nombre, string departamento, string puesto, int id, int salario, string estado)
{
    this->nombre = nombre;
    this->departamento = departamento;
    this->puesto = puesto;
    this->id = id;
    this->salario = salario;
    this->estado = estado;
}
Empleado::Empleado()
{
}
void Empleado::serialize(std::ofstream& out) const{
    // Serializar nombre
    size_t tamNombre = nombre.size();
    out.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
    out.write(nombre.c_str(), tamNombre);

    // Serializar departamento
    size_t tamDepartamento = departamento.size();
    out.write(reinterpret_cast<const char*>(&tamDepartamento), sizeof(tamDepartamento));
    out.write(departamento.c_str(), tamDepartamento);

    // Serializar puesto
    size_t tamPuesto = puesto.size();
    out.write(reinterpret_cast<const char*>(&tamPuesto), sizeof(tamPuesto));
    out.write(puesto.c_str(), tamPuesto);

    // Serializar id, salario y estado
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(reinterpret_cast<const char*>(&salario), sizeof(salario));
    out.write(reinterpret_cast<const char*>(&estado), sizeof(estado));
}


// Método para deserializar el objeto
void Empleado::deserialize(std::ifstream& in) {
    // Deserializar nombre
    size_t tamNombre;
    in.read(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
    nombre.resize(tamNombre);
    in.read(&nombre[0], tamNombre);

    // Deserializar departamento
    size_t tamDepartamento;
    in.read(reinterpret_cast<char*>(&tamDepartamento), sizeof(tamDepartamento));
    departamento.resize(tamDepartamento);
    in.read(&departamento[0], tamDepartamento);

    // Deserializar puesto
    size_t tamPuesto;
    in.read(reinterpret_cast<char*>(&tamPuesto), sizeof(tamPuesto));
    puesto.resize(tamPuesto);
    in.read(&puesto[0], tamPuesto);

    // Deserializar id, salario y estado
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&salario), sizeof(salario));
    in.read(reinterpret_cast<char*>(&estado), sizeof(estado));
}

int Empleado::getid()
{
    return this->id;
}

int Empleado::getsalario()
{
    return this->salario;
}

string Empleado::getestado()
{
    return this->estado;
}

void Empleado::setid(int id)
{
    this->id = id;
}

void Empleado::setsalario(int salario)
{
    this->salario = salario;
}

void Empleado::setestado(string estado)
{
    this->estado = estado;
}


