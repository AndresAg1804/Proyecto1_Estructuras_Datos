#include "Tabla.h"
#include "Controladora.h"

int main(void) {
	/*Tabla* Sokoban = new Tabla("../L1.txt");
	Sokoban->START();*/
	/*Controladora* control = new Controladora();
	control->Iniciar();
	delete control;*/
	char op = ' ';
	char oop = '\x1b';
	op = _getch();
	if(op == oop) std::cout << "Son iguales"  << std::endl;
	std::cout << "Valor de op: " << static_cast<int>(op) << std::endl;
	return 0;
	// hola juanpa
}