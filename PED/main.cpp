#include "Controladora.h"

int main(void) {
	Controladora* control = new Controladora();
	control->Iniciar();
	delete control;
	
	return 0;
}