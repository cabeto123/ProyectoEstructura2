#include <iostream>
#include "Empleado.h"
#include "Clientes.h"
#include "Venta.h"
#include "Pedido.h"
#include "ArbolBPlus.h"
#include "Inventario.h"
using namespace std;
void gestion_empleados() {
	int opcion = 3;
	//variables
	int id, salario;
	bool estado;
	string nombre, departamento, puesto, activo;
	ArbolBPlus arbol(3);
	ifstream archivo("empleados.bin");
	Empleado* emp = NULL;
	//fin de variables
	while (opcion != 4) {
		cout << "Que desea hacer?" << endl;
		cout << "1.Agregar empleado" << endl;
		cout << "2.Modificar empleado" << endl;
		cout << "3.Eliminar empleado" << endl;
		cout << "4.Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			cout << endl << "---Agregar empleado---" << endl;
			cout << "Digite el id de empleado: ";
			cin >> id;
			cout << endl << "Digite el nombre: ";
			cin.ignore();
			getline(cin, nombre);
			cout << endl << "Digite el departamento: ";

			getline(cin, departamento);
			cout << endl << "Digite el puesto: ";
			getline(cin, puesto);
			cout << endl << "Digite el salario: ";
			cin >> salario;
			cout << endl << "Esta activo Si/NO?: ";
			cin.ignore();
			getline(cin, activo);


			if (archivo.good())
			{
				arbol.cargarDesdeArchivoempleado("empleados.bin");

				arbol.insertarempleado(to_string(id), new Empleado(nombre, departamento, puesto, id, salario, activo));

			}
			else {
				arbol.insertarempleado(to_string(id), new Empleado(nombre, departamento, puesto, id, salario, activo));

			}
			arbol.guardarEnArchivoEmpleados("empleados.bin");
			
			cout << endl << "---Empleado agregado exitosamente---" << endl;
			break;
		case 2:
			cout << endl << "Digite el id del empleado a buscar: ";
			cin >> id;
			emp = arbol.buscarempleado(to_string(id));
			if (emp==NULL)
			{
				cout << endl << "No existe el empleado con ese id";
			}
			else {
				cout << endl << "---Modificar empleado---" << endl;
				
				cout << endl << "Digite el nombre: ";
				cin.ignore();
				getline(cin, nombre);
				emp->nombre = nombre;
				cout << endl << "Digite el departamento: ";
				getline(cin, departamento);
				emp->departamento = departamento;
				cout << endl << "Digite el puesto: ";
				getline(cin, puesto);
				emp->puesto = puesto;
				cout << endl << "Digite el salario: ";
				cin >> salario;
				emp->setsalario(salario);
				cout << endl << "Esta activo Si/NO?: ";
				cin.ignore();
				getline(cin, activo);
				emp->setestado(activo);
				cout << endl << "---Empleado modificado exitosamente---" << endl;
			}
	

			break;
		case 3:
			arbol.recorrer();

			break;

		}
	}
	cout << endl;
}
int main() {
	int opcion = 1;
	while (opcion != 6) {
		cout << "1.Gestion de empleados" << endl;
		cout << "2.Gestion de inventarios" << endl;
		cout << "3.Gestion de clientes" << endl;
		cout << "4.Gestion de ventas" << endl;
		cout << "5.Gestion de pedidos" << endl;
		cout << "6.Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			gestion_empleados();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}
	}

	return 0;
}