#include "Controladora.h"

Controladora::Controladora()
{
	tabla = nullptr;
}

Controladora::~Controladora()
{
	if(tabla != nullptr) delete tabla;
}

void Controladora::Menu()
{
	Interfaz::mostrarPantallaInicial();
    //Menu();
    //char opcion = ' ';
    //do {

    //    opcion = Interfaz::getMove(tabla);
    //    //aqui se llama al metod de los movimientos
    //} while (opcion != 'z');
}


void Controladora::Iniciar()
{
	Menu();
	system("cls");
	int opc = 0;
	do {
		try{
			opc = Interfaz::menuPrincipal();
			if (opc == -1) { // Verifica si menuPrincipal() retornó -1 (entrada inválida)
				throw std::exception("Error: Debe ingresar un número válido.");
			}	
		
			switch (opc)
			{
			case 1:
			{
				system("pause");
				system("cls");
				Control1();
				break;
			}
			case 2:
			{
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				std::cout << "Hasta pronto...\n";
				system("pause");
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menuPrincipal()
			
			std::cout << e.what() << std::endl;
			
			system("pause");
			system("cls");
		}

		if (opc != 3) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	} while (opc != 3);
}

void Controladora::Control1()
{
	int opc = 0;
	bool bandera = false;
	do {
		try {
			opc = Interfaz::menuEscogerNivel();
			if (opc == -1) { // Verifica si menuPrincipal() retornó -1 (entrada inválida)
				throw std::exception("Error: Debe ingresar un número válido.");
			}

			switch (opc)
			{
			case 1:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../L1.txt");
				control2();
				bandera = true;
				break;
			}
			case 2:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../L2.txt");
				control2();
				bandera = true;
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../L3.txt");
				control2();
				bandera = true;
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menuPrincipal()

			std::cout << e.what() << std::endl;

			system("pause");
			system("cls");
		}

		if (bandera != true) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	} while (bandera != true);
}

void Controladora::control2()
{
	char opcion = ' ';
   do {

       opcion = Interfaz::getMove(tabla);
       //aqui se llama al metod de los movimientos
   } while (opcion != 'z' && opcion != '\x1b');
}

void Controladora::control3()
{
	int opc = 0;
	bool bandera = false;
	do {
		try {
			opc = Interfaz::menuJugar();
			if (opc == -1) { // Verifica si menuPrincipal() retornó -1 (entrada inválida)
				throw std::exception("Error: Debe ingresar un número válido.");
			}

			switch (opc)
			{
			case 1:
			{
				system("pause");
				system("cls");
				

				bandera = true;
				break;
			}
			case 2:
			{
				system("pause");
				system("cls");
				tabla->restart();
				bandera = true;
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../L3.txt");
				//
				bandera = true;
				break;
			}
			case 4: {
				system("pause");
				system("cls");
				bandera = true;
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menuPrincipal()

			std::cout << e.what() << std::endl;

			system("pause");
			system("cls");
		}

		if (bandera != true) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	} while (bandera != true);
}

void Controladora::control4()
{
	int opc = 0;
	do {
		try {
			opc = Interfaz::menuGane();
			if (opc == -1) { 
				throw std::exception("Error: Debe ingresar un número válido.");
			}

			switch (opc)
			{
			case 1:
			{
				system("pause");
				system("cls");

				break;
			}
			case 2:
			{
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				std::cout << "Hasta pronto...\n";
				system("pause");
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menuPrincipal()

			std::cout << e.what() << std::endl;

			system("pause");
			system("cls");
		}

		if (opc != 3) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	} while (opc != 3);
}

void Controladora::control5()
{
}
