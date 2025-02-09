#include <iostream>
#include "Empleado.h"
#include "Venta.h"
#include "Pedido.h"
#include "ArbolBPlus.h"
using namespace std;
void gestion_empleados() {

}
int main() {
    int opcion = 1;
    while (opcion!=6) {
        cout << "1.Gestion de empleados"<<endl;
        cout << "2.Gestion de inventarios" << endl;
        cout << "3.Gestion de clientes" << endl;
        cout << "4.Gestion de ventas" << endl;
        cout << "5.Gestion de pedidos" << endl;
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