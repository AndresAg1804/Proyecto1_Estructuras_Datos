#include "Tabla.h"
#include "Controladora.h"

int main(void) {
	/*Tabla* Sokoban = new Tabla("../L1.txt");
	Sokoban->START();*/
	Controladora* control = new Controladora();
	control->Iniciar();
	delete control;
	
	return 0;
	// hola juanpa
}