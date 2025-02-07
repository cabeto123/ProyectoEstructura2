#include "Empleados.h"

int Empleados::getid()
{
    return this->id;
}

int Empleados::getsalario()
{
    return this->salario;
}

bool Empleados::getestado()
{
    return this->estado;
}

void Empleados::setid(int id)
{
    this->id = id;
}

void Empleados::setsalario(int salario)
{
    this->salario = salario;
}

void Empleados::setestado(bool estado)
{
    this->estado = estado;
}

