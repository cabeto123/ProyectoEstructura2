#include "Pedido.h"

int Pedido::getId() {
	return id;
}
vector < string > Pedido::getProductos() {
	return productos;
}
string Pedido::getCliente() {
	return cliente;
}
string Pedido::getFechaEntrega() {
	return fechaEntrega;
}
bool Pedido::estaCompletado() {
	return completado;
}
void Pedido::setEstado(bool estado) {
	completado = estado;
}