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
				throw std::exception("Error: Debe ingresar un numero valido.");
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
				tabla = new Tabla("Guardado.txt");
				if(tabla->col != 0) 
					control2();
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
			if (opc == -1) { // Verifica si menu retorno -1 (entrada invalida)
				throw std::exception("Error: Debe ingresar un numero valido.");
			}

			switch (opc)
			{
			case 1:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../Facil.txt");
				control2();
				bandera = true;
				break;
			}
			case 2:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../Medio.txt");
				control2();
				bandera = true;
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				tabla = new Tabla("../Dificil.txt");
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
		catch (const std::exception& e) { // Captura la excepción de menu

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

   } while (opcion != 'z' && opcion != '\x1b');
   if (opcion == 'z') {
	   control4();
   }
   else {
	   control3();
   }
   return;
}

void Controladora::control3()
{
	int opc = 0;
	bool bandera = false;
	do {
		try {
			opc = Interfaz::menuJugar();
			if (opc == -1) { // Verifica si menu retorno -1 (entrada invalida)
				throw std::exception("Error: Debe ingresar un numero valido.");
			}

			switch (opc)
			{
			case 1:
			{
				tabla->guardar();
				system("pause");
				system("cls");
				

				bandera = true;
				break;
			}
			case 2:
			{
				tabla = tabla->restart();
				control2();
				return;
				
				bandera = true;
				break;
			}
			case 3:
			{
				
				system("pause");
				system("cls");
				control2();
				
				bandera = true;
				break;
			}
			case 4:
			{

				system("pause");
				system("cls");
				tabla->restart();
				
				
				bandera = true;
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menu

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
				throw std::exception("Error: Debe ingresar un numero valido.");
			}

			switch (opc)
			{
			case 1:
			{
				if (tabla->getNombre() != "../Dificil.txt" && tabla->getNombre() != "Guardado.txt") {
					control6();  //siguiente nivel...
					control2();
					return; // para que no se repita el menu de ganar si avanza al siguiente nivel...
					break;

				}
				else {
					system("pause");
					system("cls");
					control7();  //mensaje de salida...
					break;
				}
				
			}
			case 2:
			{
				control5();   // repetecion...
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{
				system("pause");
				system("cls");
				break;
			}
			default: {
				throw std::exception("Rango incorrecto");
				break;
			}
			}
		}
		catch (const std::exception& e) { // Captura la excepción de menu

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
	Interfaz::getRep(tabla);
}

void Controladora::control6()
{
	tabla = Interfaz::siguienteNivel(tabla);
}

void Controladora::control7()
{
	Interfaz::mensajeSalida();
}
