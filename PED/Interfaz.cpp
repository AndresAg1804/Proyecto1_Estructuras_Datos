#include "Interfaz.h"

void Interfaz::mostrarPantallaInicial() {
    // Limpia la pantalla
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Tamaño de la pantalla (ancho)
    int screenWidth = 80;

    // Mensaje "UNA" centrado
    std::cout << std::setw((screenWidth - 3) / 2) << "" << "UNA" << std::endl;
    std::cout << '\n' << '\n';

    // Arte ASCII centrado
    std::cout << std::setw((screenWidth - 43) / 2) << "" << "SSSSS  OOO  K   K  OOO  BBBBB    AAA    N   N" << std::endl;
    std::cout << std::setw((screenWidth - 43) / 2) << "" << "S     O   O K  K  O   O B   B   A   A   NN  N" << std::endl;
    std::cout << std::setw((screenWidth - 43) / 2) << "" << " SSS  O   O KK    O   O BBBBB  AAAAAAA  N N N" << std::endl;
    std::cout << std::setw((screenWidth - 43) / 2) << "" << "    S O   O K K   O   O B   B  A     A  N  NN" << std::endl;
    std::cout << std::setw((screenWidth - 43) / 2) << "" << "SSSSS  OOO  K   K  OOO  BBBBB A       A N   N" << std::endl;
    std::cout << '\n' << '\n';

    // Mensajes "JUANPA", "ANNER", "MARCOS" centrados
    std::cout << std::setw((screenWidth - 30) / 2) << "" << "Juan Pablo Cartin Esquivel" << std::endl;
    std::cout << std::setw((screenWidth - 30) / 2) << "" << "Anner Andres Angulo Gutierrez" << std::endl;
    std::cout << std::setw((screenWidth - 30) / 2) << "" << "Marcos Emilio Vasquez Diaz" << std::endl;

    std::cout << '\n' << '\n' << '\n' << '\n';

    std::cout << "Presiona cualquier tecla para comenzar..." << std::endl;

    // Espera a que el jugador presione una tecla
    //std::cin.ignore();
    std::cin.get();
}

int Interfaz::menuPrincipal()
{
    int opc = 0;
    std::cout << "                      MENU                      \n";
    std::cout << "1. Nuevo Juego\n";
    std::cout << "2. Cargar Juego Guardado \n";
    std::cout << "3. Salir \n";
    std::cout << "Digite una opcion del menu: ";
    if (std::cin >> opc) {
        return opc;
    }
    else {
        return -1; // Retorna -1 en caso de entrada inválida
    }

}

int Interfaz::menuJugar()
{
    int opc = 0;
    std::cout << "                      MENU                      \n";
    std::cout << "1. Guardar juego y salir al menu principal\n";
    std::cout << "2. Reiniciar Nivel \n";
    std::cout << "3. Volver al juego \n";
    std::cout << "4. Salir al menu principal (No guarda la partida)\n";
    std::cout << "Digite una opcion del menu: ";
    if (std::cin >> opc) {
        return opc;
    }
    else {
        return -1; // Retorna -1 en caso de entrada inválida
    }
}

int Interfaz::menuEscogerNivel()
{
    int opc = 0;
    std::cout << "                      MENU                      \n";
    std::cout << "1. Dificultad Facil\n";
    std::cout << "2. Dificultad Media\n";
    std::cout << "3. Dificultad Dificil\n";
    std::cout << "Digite una opcion del menu: ";
    if (std::cin >> opc) {
		return opc;
	}
    else {
		return -1; // Retorna -1 en caso de entrada inválida
	}
}

char Interfaz::getMove(Tabla* table) {
    char op = 'x';
    while (op != '\x1b') {
        if (table->endGAME.empty()) {
            std::cout << "Win Win!!!" << '\n';
            op = 'z';
            return op;
        }
        std::cout << table->toString();
        std::cout << '\n' << '\n';
        std::cout << table->movimientos();
        std::cout << '\n' << '\n';

        try {
            op = _getch();

            std::system("cls");

            // Verifica si el movimiento es válido
            bool validMove = false;

            switch (op) {
            case 'w': validMove = table->moveUp(); table->rep.push_back('w'); break;   // 'w' en ASCII  
            case 'a': validMove = table->moveLeft(); table->rep.push_back('a'); break;  // 'a' en ASCII  
            case 'd': validMove = table->moveRight(); table->rep.push_back('d'); break; // 'd' en ASCII  
            case 's': validMove = table->moveDown(); table->rep.push_back('s'); break;  // 's' en ASCII  
            case '\x1b': validMove = true; break; // 'z' en ASCII
            default: break;
            }

            if (validMove) {
                // Realiza el movimiento si es válido
                std::cout << "Movimiento realizado:\n";
            }
            else {
                std::cout << "Movimiento no valido. Intente de nuevo.\n\n\n";
            }
        }
        catch (...) {
            std::cout << "Por favor, ingrese un caracter valido.\n";
        }
    }
    return op;
}

std::string Interfaz::getRep(Tabla* table)
{
    std::stringstream s;
    int i = 0; 

    // Limpia la pantalla antes de comenzar
    std::system("cls");

    std::vector <char> rep2;
    rep2 = table->rep;
    table = table->restart();
    for (char movimiento : rep2) {
        switch (movimiento) {
        case 'w':
            (*table).moveUp();
            break;
        case 'a':
            (*table).moveLeft();
            break;
        case 'd':
            (*table).moveRight();
            break;
        case 's':
            (*table).moveDown();
            break;
        }

        std::system("cls");

        std::cout << "Movimiento #" << i << " '" << movimiento << "':\n";

        std::cout << table->toString() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(225));

        i++;
    }

    return s.str();
}

int Interfaz::menuGane()
{
    int opc = 0;
    std::cout << "                      MENU                      \n";
    std::cout << "1. Avanzar al siguiente nivel\n";
    std::cout << "2. Ver Repeticion\n";
    std::cout << "3. Salir al menu principal\n";
    std::cout << "Digite una opcion del menu: ";
    if (std::cin >> opc) {
        return opc;
    }
    else {
        return -1; // Retorna -1 en caso de entrada inválida
    }
}

Tabla* Interfaz::siguienteNivel(Tabla* tabla)
{
    if (tabla->getNombre() == "../Facil.txt")
    {
        delete tabla;
		tabla = new Tabla("../Medio.txt");
		return tabla;
	}
    else if (tabla->getNombre() == "../Medio.txt")
    {
        delete tabla;
		tabla = new Tabla("../Dificil.txt");
		return tabla;
	}
    else if (tabla->getNombre() == "../Dificil.txt") {
        return tabla;
    }
    return 0;
}

void Interfaz::mensajeSalida()
{
    std::cout << '\n' << '\n';

    std::cout << "Ya no hay mas niveles \n";

    std::cout << '\n' << '\n';

    std::cout << "    ####     ##     ##   ##  #######            #####   ##   ##  #######  ###### \n";
    std::cout << "   ##  ##   ####    ### ###   ##   #           ##   ##  ##   ##   ##   #   ##  ## \n";
    std::cout << "  ##       ##  ##   #######   ## #             ##   ##   ## ##    ## #     ##  ## \n";
    std::cout << "  ##       ##  ##   #######   ####             ##   ##   ## ##    ####     ##### \n";
    std::cout << "  ##  ###  ######   ## # ##   ## #             ##   ##    ###     ## #     ## ## \n";
    std::cout << "   ##  ##  ##  ##   ##   ##   ##   #           ##   ##    ###     ##   #   ##  ## \n";
    std::cout << "    #####  ##  ##   ##   ##  #######            #####      #     #######  #### ## \n";

    std::cout << '\n' << '\n';

    std::cout << "  ##   ##  #######  ##   ##   #####   ######   ##  ##            ####     #######    ##     ###  ##           #### \n";
    std::cout << "  ### ###   ##   #  ### ###  ##   ##   ##  ##  ##  ##             ##       ##   #   ####     ##  ##          ##  ## \n";
    std::cout << "  #######   ## #    #######  ##   ##   ##  ##  ##  ##             ##       ## #    ##  ##    ## ##               ## \n";
    std::cout << "  #######   ####    #######  ##   ##   #####    ####              ##       ####    ##  ##    ####               ## \n";
    std::cout << "  ## # ##   ## #    ## # ##  ##   ##   ## ##     ##               ##   #   ## #    ######    ## ##             ## \n";
    std::cout << "  ##   ##   ##   #  ##   ##  ##   ##   ##  ##    ##               ##  ##   ##   #  ##  ##    ##  ##\n";
    std::cout << "  ##   ##  #######  ##   ##   #####   #### ##   ####             #######  #######  ##  ##   ###  ##            ## \n";

    std::cout << '\n' << '\n';

    std::cout<<"Gracias por jugar Sokoban UNA \n";

}
