#include "Empleado.h"

int Empleado::getid()
{
    return this->id;
}

int Empleado::getsalario()
{
    return this->salario;
}

bool Empleado::getestado()
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

void Empleado::setestado(bool estado)
{
    this->estado = estado;
}

