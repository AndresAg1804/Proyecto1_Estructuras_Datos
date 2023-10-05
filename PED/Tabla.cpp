#include "Tabla.h"


// ANSI escape codes for text colors
#define ANSI_RESET "\033[0m" 
#define ANSI_RED "\033[31m" 
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m" 


void mostrarPantallaInicial() {
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
    std::cout << std::setw((screenWidth - 3) / 2) << "" << "JUANPA" << std::endl;
    std::cout << std::setw((screenWidth - 3) / 2) << "" << "ANNER" << std::endl;
    std::cout << std::setw((screenWidth - 3) / 2) << "" << "MARCOS" << std::endl;

    std::cout << '\n' << '\n' << '\n' << '\n';

    std::cout << "Presiona cualquier tecla para comenzar..." << std::endl;

    // Espera a que el jugador presione una tecla
    std::cin.ignore();
    std::cin.get();
}



int Tabla::leerCol(const std::string& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return 0;
    }


    Tabla::Nodo* aux = this->inicio;
    std::string l;
    int conta=0;
    archivo >> l;
    conta=(int)l.size();

    archivo.close();
    return conta;
}

int Tabla::leerfil(const std::string& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return 0;
    }


    Tabla::Nodo* aux = this->inicio;
    std::string l;
    int conta=0;
    while (getline(archivo, l))
    {
        conta++;
    }

 
    archivo.close();
    return conta;
}

Tabla::Tabla(const std::string& nombreArchivo)
{
    this->inicio = nullptr;
    this->jugador = nullptr;
    this->col = leerCol(nombreArchivo);
    this->fil = leerfil(nombreArchivo);

        Nodo*** matrix = new Nodo ** [this->fil];
        for (int i = 0; i < this->fil; i++) {
            matrix[i] = new Nodo*[this->col];
        }

        for (int i = 0; i < this->fil; i++) {
            for (int j = 0; j < this->col; j++) {
                matrix[i][j] = new Nodo('.',nullptr, nullptr, nullptr, nullptr);
            }
        }


        this->inicio = matrix[0][0];

        for (int i = 0; i < fil; i++) {
            for (int j = 0; j < col; j++) {
                if (i > 0) {
                    matrix[i][j]->up = matrix[i - 1][j];
                }

                if (i < fil - 1) {
                    matrix[i][j]->down = matrix[i + 1][j];
                }

                if (j > 0) {
                    matrix[i][j]->left = matrix[i][j - 1];
                }

                if (j < col - 1) {
                    matrix[i][j]->right = matrix[i][j + 1];
                }
            }
        }
        /// ////////////////////////////////////////////////////////////////////////////////

        std::ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
            return;
        }

        std::string line;
        int row = 0;

        while (std::getline(archivo, line) && row < this->fil) {
            int col = 0;
            for (char c : line) {
                if (col < this->col) {
                    if (c == '$') {
                        this->endGAME.push(1);//can de $
                    }
                    if (c == '@') {
                        this->jugador =matrix[row][col]; //Para saber donde esta el jugador siempre
                        matrix[row][col]->punto = false;
                    }

                    if (c == ',') {
                        matrix[row][col]->setdata(' ');
                        matrix[row][col]->punto = false;
                    }
                    else {
                        matrix[row][col]->setdata(c);
                        if (c == '.') {
                            matrix[row][col]->punto = true;
                        }
                    }

                    col++;
                }
            }
            row++;
        }
        archivo.close();
        ////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < this->fil; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
}

std::string Tabla::toString() {
    std::stringstream s;
    char cell = ' ';
    Nodo* aux = this->inicio;
    Nodo* actual = this->inicio;

    for (int i = 0; i < this->fil; i++) {
        for (int j = 0; j < this->col; j++) {
            if (actual != nullptr) {
                cell = actual->data;
                actual = actual->right;
            }
            switch (cell) {
            case '@':
                s << ANSI_CYAN << cell << ANSI_RESET;  // Cyan color for the player character
                break;
            case '.':
                s << ANSI_GREEN << cell << ANSI_RESET;  // White color for dots 
                break;
            case '$':
                s << ANSI_YELLOW << cell << ANSI_RESET; // Yellow color for dollar signs
                break;
            case '!':
                s << ANSI_RED << cell << ANSI_RESET;    // Red color for exclamation marks
                break;
            default:
                s << cell;  // No color for other characters
            }
        }
        s << '\n';
        if (i < this->fil - 1) {
            aux = aux->down;
            actual = aux;
        }
    }

    return s.str();
}


void Tabla::START()
{
    mostrarPantallaInicial();
    char op;
    do {
        
        op = getMove();
        //aqui se llama al metod de los movimientos
    } while (op != 'z');
}

char Tabla::getMove() {
    char op = 'x';
    while (op != 'z') {
        if (this->endGAME.empty()) {
            std::cout<<"Win Win!!!"<<'\n';
            op = 'z';
            return op;
        }
        std::cout << this->toString();
        std::cout << '\n' << '\n';
        std::cout << "      { 'z' :(EXIT)}" << '\n' << '\n';
        std::cout << "  w:(up)\n";
        std::cout << "a:(left)   +   d:(right)\n";
        std::cout << "  s:(down)\n";
        std::cout << '\n' << '\n';

        try {
            op = _getch();
            std::system("cls");

            // Verifica si el movimiento es válido
            bool validMove = false;

            switch (op) {
            case 'w': validMove = moveUp(); break;
            case 'a': validMove = moveLeft(); break;
            case 'd': validMove = moveRight(); break;
            case 's': validMove = moveDown(); break;
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

bool Tabla::moveUp() {
    if (this->jugador->up) {
        char nextUp = this->jugador->up->data;
        char previousData = this->jugador->data;

        if (nextUp == ' ') {
            this->jugador->up->data = '@';
            this->jugador->data = ' ';
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->up;
            return true;
        }
        else if (nextUp == '.') {
            if (previousData == '.') {
                this->jugador->up->data = '@';
                this->jugador->data = ' ';
            }
            else {
                this->jugador->up->data = '@';
                this->jugador->data = ' ';
            }
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->up;
            return true;
        }
        else if (nextUp == '$') {
            char nextNextUp = this->jugador->up->up->data;
            if (nextNextUp == ' ' || nextNextUp == '.') {
                if (nextNextUp == '.') {
                    this->jugador->up->up->data = '!';
                    this->endGAME.pop();
                }
                else {
                    this->jugador->up->up->data = '$';
                }
                this->jugador->up->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->up;
                return true;
            }
        }
        else if (nextUp == '!') {
            char nextNextUp = this->jugador->up->up->data;
            if (nextNextUp == ' ') {
                this->jugador->up->up->data = '$';
                this->jugador->up->data = '@';
                this->jugador->data = ' ';
                this->endGAME.push(1);
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->up;
                return true;
            }
            if (nextNextUp == '.') {
                this->jugador->up->up->data = '!';
                this->jugador->up->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto == true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->up;
                return true;
            }
        }
    }
    return false;
}
bool Tabla::moveDown() {
    if (this->jugador->down) {
        char nextDown = this->jugador->down->data;
        char previousData = this->jugador->data;

        if (nextDown == ' ') {
            this->jugador->down->data = '@';
            this->jugador->data = ' ';
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->down;
            return true;
        }
        else if (nextDown == '.') {
            if (previousData == '.') {
                this->jugador->down->data = '@';
                this->jugador->data = ' ';
            }
            else {
                this->jugador->down->data = '@';
                this->jugador->data = ' ';
            }
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->down;
            return true;
        }
        else if (nextDown == '$') {
            char nextNextDown = this->jugador->down->down->data;
            if (nextNextDown == ' ' || nextNextDown == '.') {
                if (nextNextDown == '.') {
                    this->jugador->down->down->data = '!';
                    this->endGAME.pop();
                }
                else {
                    this->jugador->down->down->data = '$';
                }
                this->jugador->down->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->down;
                return true;
            }
        }
        else if (nextDown == '!') {
            char nextNextDown = this->jugador->down->down->data;
            if (nextNextDown == ' ') {
                this->jugador->down->down->data = '$';
                this->jugador->down->data = '@';
                this->jugador->data = ' ';
                this->endGAME.push(1);
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->down;
                return true;
            }
            if (nextNextDown == '.') {
                this->jugador->down->down->data = '!';
                this->jugador->down->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto == true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->down;
                return true;
            }
        }
    }

    return false;
}

bool Tabla::moveLeft() {
    if (this->jugador->left) {
        char nextLeft = this->jugador->left->data;
        char previousData = this->jugador->data;

        if (nextLeft == ' ') {
            this->jugador->left->data = '@';
            this->jugador->data = ' ';
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->left;
            return true;
        }
        else if (nextLeft == '.') {
            if (previousData == '.') {
                this->jugador->left->data = '@';
                this->jugador->data = ' ';
            }
            else {
                this->jugador->left->data = '@';
                this->jugador->data = ' ';
            }
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->left;
            return true;
        }
        else if (nextLeft == '$') {
            char nextNextLeft = this->jugador->left->left->data;
            if (nextNextLeft == ' ' || nextNextLeft == '.') {
                if (nextNextLeft == '.') {
                    this->jugador->left->left->data = '!';
                    this->endGAME.pop();
                }
                else {
                    this->jugador->left->left->data = '$';
                }
                this->jugador->left->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->left;
                return true;
            }
        }
        else if (nextLeft == '!') {
            char nextNextLeft = this->jugador->left->left->data;
            if (nextNextLeft == ' ') {
                this->jugador->left->left->data = '$';
                this->jugador->left->data = '@';
                this->jugador->data = ' ';
                this->endGAME.push(1);
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->left;
                return true;
            }
            if (nextNextLeft == '.') {
                this->jugador->left->left->data = '!';
                this->jugador->left->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto == true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->left;
                return true;
            }
        }
    }

    return false;
}

bool Tabla::moveRight() {
    if (this->jugador->right) {
        char nextRight = this->jugador->right->data;
        char previousData = this->jugador->data;

        if (nextRight == ' ') {
            this->jugador->right->data = '@';
            this->jugador->data = ' ';
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->right;
            return true;
        }
        else if (nextRight == '.') {
            if (previousData == '.') {
                this->jugador->right->data = '@';
                this->jugador->data = ' ';
            }
            else {
                this->jugador->right->data = '@';
                this->jugador->data = ' ';
            }
            if (this->jugador->punto==true) {
                this->jugador->data = '.';
            }
            this->jugador = this->jugador->right;
            return true;
        }
        else if (nextRight == '$') {
            char nextNextRight = this->jugador->right->right->data;
            if (nextNextRight == ' ' || nextNextRight == '.') {
                if (nextNextRight == '.') {
                    this->jugador->right->right->data = '!';
                    this->endGAME.pop();
                }
                else {
                    this->jugador->right->right->data = '$';
                }
                this->jugador->right->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->right;
                return true;
            }
        }
        else if (nextRight == '!') {
            char nextNextRight = this->jugador->right->right->data;
            if (nextNextRight ==' '){
                this->jugador->right->right->data = '$';
                this->jugador->right->data = '@';
                this->jugador->data = ' ';
                this->endGAME.push(1);
                if (this->jugador->punto==true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->right;
                return true;
            }
            if (nextNextRight == '.') {
                this->jugador->right->right->data = '!';
                this->jugador->right->data = '@';
                this->jugador->data = ' ';
                if (this->jugador->punto == true) {
                    this->jugador->data = '.';
                }
                this->jugador = this->jugador->right;
                return true;
            }
        }
    }

    return false;
}











/*
void Tabla::START()
{
    int op;
    do {

        op = getMove();
        //aqui se llama al metod de los movimientos
    } while (op != 'z');
}

int Tabla::getMove() {
    char op = 'x';
    while ((op != 'z')) {
        std::cout << this->toString();
        std::cout << '\n' << '\n';
        std::cout << "      { 'z' :(EXIT)}" << '\n' << '\n';
        std::cout << "	w:(up)" << '\n';
        std::cout << "a:(left)   +   d:(right)" << '\n';
        std::cout << "	s:(down)" << '\n';
        std::cout << '\n' << '\n';
        try {
            std::cin >> op;
            if (op != 'a' && op != 'b' && op != 'w' && op != 's' && op != 'z') {
                op = 'x';
            }
            std::system("cls");
        }
        catch (...) {
            std::cout << "Please enter a valid char." << '\n';
            std::system("cls");
        }
    }
    return op;
}
*/


/*
bool Tabla::moveUp()
{
    if (this->jugador->up) {
        char nextUp = this->jugador->up->data;
        if (nextUp == ' ' || nextUp == '.') {
            if (nextUp == '.') {
                // Si hay un espacio para colocar una caja, verifica si hay una caja arriba de la posición actual.
                if (this->jugador->up->up && this->jugador->up->up->data == '$') {
                    this->jugador->up->up->data = '!';
                }
                else {
                    this->jugador->up->up->data = '$';
                }
            }
            this->jugador->up->data = '@';
            this->jugador->data = (this->jugador->data == '@' && this->jugador->up->up && this->jugador->up->up->data == '!') ? '.' : ' ';
            this->jugador = this->jugador->up;
            return true;
        }
        // Si el siguiente espacio contiene una caja, intenta mover la caja si es posible.
        if (nextUp == '$' || nextUp == '!') {
            char nextNextUp = this->jugador->up->up ? this->jugador->up->up->data : ' ';
            if (nextNextUp == ' ' || nextNextUp == '.') {
                // Mueve la caja hacia arriba.
                if (nextUp == '!') {
                    this->jugador->up->up->data = '!';
                }
                else {
                    this->jugador->up->up->data = '$';
                }
                this->jugador->up->data = '@';
                this->jugador->data = (this->jugador->data == '@' && nextNextUp == '!') ? '.' : ' ';
                this->jugador = this->jugador->up;
                return true;
            }
        }
    }
    return false;
}

bool Tabla::moveDown()
{
    if (this->jugador->down) {
        char nextDown = this->jugador->down->data;
        if (nextDown == ' ' || nextDown == '.') {
            if (nextDown == '.') {
                // Si hay un espacio para colocar una caja, verifica si hay una caja abajo de la posición actual.
                if (this->jugador->down->down && this->jugador->down->down->data == '$') {
                    this->jugador->down->down->data = '!';
                }
                else {
                    this->jugador->down->down->data = '$';
                }
            }
            this->jugador->down->data = '@';
            this->jugador->data = (this->jugador->data == '@' && this->jugador->down->down && this->jugador->down->down->data == '!') ? '.' : ' ';
            this->jugador = this->jugador->down;
            return true;
        }
        if (nextDown == '$' || nextDown == '!') {
            char nextNextDown = this->jugador->down->down ? this->jugador->down->down->data : ' ';
            if (nextNextDown == ' ' || nextNextDown == '.') {
                if (nextDown == '!') {
                    this->jugador->down->down->data = '!';
                }
                else {
                    this->jugador->down->down->data = '$';
                }
                this->jugador->down->data = '@';
                this->jugador->data = (this->jugador->data == '@' && nextNextDown == '!') ? '.' : ' ';
                this->jugador = this->jugador->down;
                return true;
            }
        }
    }
    return false;
}

bool Tabla::moveLeft()
{
    if (this->jugador->left) {
        char nextLeft = this->jugador->left->data;
        if (nextLeft == ' ' || nextLeft == '.') {
            if (nextLeft == '.') {
                if (this->jugador->left->left && this->jugador->left->left->data == '$') {
                    this->jugador->left->left->data = '!';
                }
                else {
                    this->jugador->left->left->data = '$';
                }
            }
            this->jugador->left->data = '@';
            this->jugador->data = (this->jugador->data == '@' && this->jugador->left->left && this->jugador->left->left->data == '!') ? '.' : ' ';
            this->jugador = this->jugador->left;
            return true;
        }
        if (nextLeft == '$' || nextLeft == '!') {
            char nextNextLeft = this->jugador->left->left ? this->jugador->left->left->data : ' ';
            if (nextNextLeft == ' ' || nextNextLeft == '.') {
                if (nextLeft == '!') {
                    this->jugador->left->left->data = '!';
                }
                else {
                    this->jugador->left->left->data = '$';
                }
                this->jugador->left->data = '@';
                this->jugador->data = (this->jugador->data == '@' && nextNextLeft == '!') ? '.' : ' ';
                this->jugador = this->jugador->left;
                return true;
            }
        }
    }
    return false;
}

bool Tabla::moveRight()
{
    if (this->jugador->right) {
        char nextRight = this->jugador->right->data;
        if (nextRight == ' ' || nextRight == '.') {
            if (nextRight == '.') {
                if (this->jugador->right->right && this->jugador->right->right->data == '$') {
                    this->jugador->right->right->data = '!';
                }
                else {
                    this->jugador->right->right->data = '$';
                }
            }
            this->jugador->right->data = '@';
            this->jugador->data = (this->jugador->data == '@' && this->jugador->right->right && this->jugador->right->right->data == '!') ? '.' : ' ';
            this->jugador = this->jugador->right;
            return true;
        }
        if (nextRight == '$' || nextRight == '!') {
            char nextNextRight = this->jugador->right->right ? this->jugador->right->right->data : ' ';
            if (nextNextRight == ' ' || nextNextRight == '.') {
                if (nextRight == '!') {
                    this->jugador->right->right->data = '!';
                }
                else {
                    this->jugador->right->right->data = '$';
                }
                this->jugador->right->data = '@';
                this->jugador->data = (this->jugador->data == '@' && nextNextRight == '!') ? '.' : ' ';
                this->jugador = this->jugador->right;
                return true;

            }
        }
    }
}
*/