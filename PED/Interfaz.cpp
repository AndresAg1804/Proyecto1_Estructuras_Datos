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
        if (table->isEnd()) {
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
            case '\x1b': break; // 'z' en ASCII
            default: break;
            }

            if (validMove) {
                // Realiza el movimiento si es válido
                std::cout << "Movimiento realizado:\n";
            }
            else {
                std::cout << "Movimiento no válido. Intente de nuevo.\n\n\n";
            }
        }
        catch (...) {
            std::cout << "Por favor, ingrese un carácter válido.\n";
        }
    }
    return op;
}

std::string Interfaz::getRep(Tabla* table)
{
    std::stringstream s;
    int i = 0;  // Contador de movimientos
    int j = 0;

    // Limpia la pantalla antes de comenzar
    std::system("cls");

    // Clona el juego original
    std::vector <char> rep2;
    //table = table->restart();
    rep2 = table->rep;
    table = table->restart();
    for (char movimiento : rep2) {
        // Realiza el movimiento en el juego clonado
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
        //rep2.push_back(movimiento);
        //table->rep = rep2;
        // Limpia la pantalla antes de mostrar el siguiente movimiento
        std::system("cls");
        //// Imprime el estado del juego después de cada movimiento
        std::cout << "Movimiento #" << i << " '" << movimiento << "':\n";

        //// Espera un momento antes de mostrar el siguiente movimiento (ajusta la duración según sea necesario)
        std::cout << table->toString() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        //std::system("cls");

        // Si el juego clonado ha llegado al estado de ganado, reinícialo
        i++;
    }

    //int inicio = 0;
    //int fin = rep2.size() - 1;

    //while (inicio < fin) {
    //    // Intercambiar el elemento en la posición 'inicio' con el elemento en la posición 'fin'
    //    std::swap(rep2[inicio], rep2[fin]);

    //    // Mover los índices hacia adentro
    //    inicio++;
    //    fin--;
    //}

    //table = table->restart();
    //for (int i = 0; i < rep2.size(); i++) {
    //    for (char movimiento2 : rep2) {
    //        // Realiza el movimiento en el juego clonado
    //        switch (movimiento2) {
    //        case 'w':
    //            (*table).moveUp();
    //            break;
    //        case 'a':
    //            (*table).moveLeft();
    //            break;
    //        case 'd':
    //            (*table).moveRight();
    //            break;
    //        case 's':
    //            (*table).moveDown();
    //            break;
    //        }
    //        std::system("cls");
    //        // Imprime el estado del juego después de cada movimiento
    //        //std::cout << "Movimiento #" << i << " '" << movimiento << "':\n";

    //        // Espera un momento antes de mostrar el siguiente movimiento (ajusta la duración según sea necesario)
    //        rep2.push_back(movimiento2);
    //        std::cout << table->toString() << '\n';
    //        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    //        j++;
    //    }
    //}

    // Ahora puedes usar rep2 para mostrar la repetición completa
    //int j = 1;
    //for (char movimiento : rep2) {
    //        std::cout << clonedGame->toString() << '\n';
    //        // Imprime el estado del juego después de cada movimiento
    //        std::cout << "Movimiento #" << i << " '" << movimiento << "':\n";

    //        // Espera un momento antes de mostrar el siguiente movimiento (ajusta la duración según sea necesario)
    //        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //        std::system("cls");

    //        j++;
    //}

    // Imprime el estado final del juego

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
