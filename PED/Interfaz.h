#pragma once
#include "Tabla.h"
#include "ExcepcionRango.h"
#include "ExcepcionValor.h"

class Interfaz
{
public:
	static void mostrarPantallaInicial();
	static int menuPrincipal();
	static int menuJugar();
	static int menuEscogerNivel();
	static char getMove(Tabla*);
	static std::string getRep(Tabla*);
	static int menuGane();
	void limpiarPantalla();
};

