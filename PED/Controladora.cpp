#include "Controladora.h"

Controladora::Controladora()
{
	tabla = new Tabla("../L1.txt");
}

Controladora::~Controladora()
{
	if(tabla != nullptr) delete tabla;
}

void Controladora::Iniciar()
{
    Menu();
    char opcion = ' ';
    do {

        opcion = Interfaz::getMove(tabla);
        //aqui se llama al metod de los movimientos
    } while (opcion != 'z');
}


void Controladora::Menu()
{
	Interfaz::mostrarPantallaInicial();

}

void Controladora::Control1()
{
	Interfaz::getMove(tabla);
}
