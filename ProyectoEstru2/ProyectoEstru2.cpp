#include <iostream>
#include "Empleado.h"
#include "Clientes.h"
#include "Venta.h"
#include "Pedido.h"
#include "ArbolBPlus.h"
#include "Inventario.h"
#include "ModuloPadre.h"

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
	Empleado* aux = new Empleado();
	//fin de variables
	while (opcion != 4) {
		cout << "Menu Gestion empleados" << endl;
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
				arbol.cargarDesdeArchivo(aux,"empleados.bin");
				arbol.insertar(to_string(id), new Empleado(nombre, departamento, puesto, id, salario, activo));

			}
			else {
				arbol.insertar(to_string(id), new Empleado(nombre, departamento, puesto, id, salario, activo));

			}
			arbol.guardarEnArchivo(aux, "empleados.bin");
			cout << endl << "---Empleado agregado exitosamente---" << endl;
			break;
		case 2:
			arbol.cargarDesdeArchivo(aux, "empleados.bin");
			cout << endl << "Digite el id del empleado a buscar: ";
			cin >> id;
			emp =reinterpret_cast<Empleado*>( arbol.buscar(to_string(id),new Empleado()));
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
void gestion_inventarios() {
	Inventario inventario;

	// Crear algunos productos
	Producto* p1 = new Producto("001", "Laptop", "Electrónica", 1200.50, 10, true);
	Producto* p2 = new Producto("002", "Smartphone", "Electrónica", 800.00, 15, true);
	Producto* p3 = new Producto("003", "Mesa", "Muebles", 150.75, 5, true);
	Producto* p4 = new Producto("004", "Silla", "Muebles", 50.25, 20, true);
	Producto* p5 = new Producto("005", "Tablet", "Electrónica", 300.00, 8, true);

	inventario.agregarProducto(p1);
	inventario.agregarProducto(p2);
	inventario.agregarProducto(p3);
	inventario.agregarProducto(p4);
	inventario.agregarProducto(p5);
	std::cout << "\n\n=== Gestor de inventarios ===" << std::endl;
	std::cout << "=== Buscar producto por ID ===" << std::endl;
	Producto* producto = inventario.buscarPorId("002");
	if (producto != nullptr) {
		std::cout << "Producto encontrado: " << producto->nombre
			<< ", Categoría: " << producto->categoria
			<< ", Precio: $" << producto->precio << std::endl;
	}
	else {
		std::cout << "Producto no encontrado." << std::endl;
	}

	std::cout << "\n=== Buscar productos por categoría ===" << std::endl;
	std::vector<Producto*> productosElectronica = inventario.buscarPorCategoria("Electrónica");
	std::cout << "Productos en la categoría Electrónica: " << productosElectronica.size() << std::endl;
	for (Producto* p : productosElectronica) {
		std::cout << " - " << p->nombre << " (ID: " << p->id << ")" << std::endl;
	}

	std::cout << "\n=== Recorrer inventario ===" << std::endl;
	inventario.recorrerInventario();

	
	std::cout << "\n=== Fin de gestor de inventarios === \n\n" << std::endl;
	return;
}
void gestion_clientes() {
	int opcion = 1;
	ArbolBPlus arbol(3);  // Asumiendo que el grado del árbol es 3
	ifstream archivo("clientes.bin");
	Clientes* cliente = nullptr;
	Clientes* aux = new Clientes();

	while (opcion != 5) {
		cout << "Menu Gestion de Clientes" << endl;
		cout << "1. Agregar cliente" << endl;
		cout << "2. Modificar cliente" << endl;
		cout << "3. Eliminar cliente" << endl;
		cout << "4. Buscar clientes con saldo mayor a X" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion) {
			// ... (otros casos)

		case 4: {
			double saldoMinimo;
			cout << endl << "Digite el saldo minimo para buscar clientes: ";
			cin >> saldoMinimo;

			// Llamar a la función buscarClientesConSaldoMayorA
			std::vector<Clientes*> clientes = arbol.buscarClientesConSaldoMayorA(saldoMinimo);

			// Mostrar los clientes encontrados
			cout << "Clientes con saldo mayor a " << saldoMinimo << ":" << endl;
			for (Clientes* c : clientes) {
				cout << "ID: " << c->id << ", Nombre: " << c->nombre << ", Saldo: " << c->saldo << endl;
			}
			break;
		}

		}
	}
	delete aux;
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
			gestion_inventarios();
			break;
		case 3:
			gestion_clientes();
			break;
		case 4:
			break;
		case 5:
			break;
		}
	}

	return 0;
}