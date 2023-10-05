#pragma once
#include "Interfaz.h"
class Controladora
{
private:
	Tabla* tabla;

public:
	Controladora();
	~Controladora();
	void Iniciar();
	void Menu();
	void Control1();
	/*void Ingresar();
	void Mostrar();
	void Buscar();
	void Eliminar();
	void Modificar();
	void Guardar();
	void Cargar();
	void Salir();*/
};

