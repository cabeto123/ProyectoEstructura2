#pragma once
#include <string>
using namespace std;
class Empleados
{
	private:
		int id;
		int salario;
		bool estado;
	public:
		string nombre,departamento, puesto;
		int getid();
		int getsalario();
		bool getestado();
		void setid(int id);
		void setsalario(int salario);
		void setestado(bool estado);

};

