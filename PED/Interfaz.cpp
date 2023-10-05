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

char Interfaz::getMove(Tabla* table) {
    char op = 'x';
    while (op != 'z') {
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
            case 'w': validMove = table->moveUp(); break;
            case 'a': validMove = table->moveLeft(); break;
            case 'd': validMove = table->moveRight(); break;
            case 's': validMove = table->moveDown(); break;
            case 'z': break;
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
            std::cout << "Por favor, ingresa un carácter válido.\n";
        }
    }
    return op;
}

