#pragma once
#include <string>
#include "ModuloPadre.h"
using namespace std;
class Empleado:public ModuloPadre
{
	public:
		int id;
		int salario;
		string estado;
	public:
		string nombre,departamento, puesto;
		Empleado(string nombre, string departamento, string puesto, int id, int salario, string estado);
		Empleado();
		int getid();
		int getsalario();
		string getestado();
		void setid(int id);
		void setsalario(int salario);
		void setestado(string estado);
		void serialize(std::ofstream& out) const;
		 void deserialize(std::ifstream& in);
};

