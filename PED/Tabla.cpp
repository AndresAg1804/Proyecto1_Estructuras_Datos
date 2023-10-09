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

Tabla::Tabla(const std::string& nombreArchivo) {
    nomArchivo = nombreArchivo;
    this->inicio = nullptr;
    this->jugador = nullptr;
    this->col = leerCol(nombreArchivo);
    this->fil = leerfil(nombreArchivo);

    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string line;
    bool start = false;
    bool startstart = false;
    bool prifilaB = true;
    Nodo* ante = nullptr;
    Nodo* priFila = nullptr;
    Nodo* nuevo = nullptr;
    int row = 0;
    while (std::getline(archivo, line) && row < this->fil) {
        int col = 0;
        for (char c : line) {
            if (col < this->col) {
                if (start == false) {
                    nuevo = new Nodo(c, nullptr, nullptr, nullptr, nullptr);
                    if (startstart == false) {
                        this->inicio = nuevo;
                        startstart = true;
                    }
                    priFila = nuevo;
                    ante = nuevo;
                    start = true;
                    if (c == '$') {
                        this->endGAME.push(1);//can de $
                    }
                    if (c == '@') {
                        this->jugador = nuevo; //Para saber donde esta el jugador siempre
                        this->jugador->punto = false;
                    }

                    if (c == ',') {
                        nuevo->setdata(' ');
                        nuevo->punto = false;
                    }
                    else {
                        nuevo->setdata(c);
                        if (c == '.') {
                            nuevo->punto = true;
                        }
                    }
                }
                else {
                    if (prifilaB == true) {
                        nuevo = new Nodo(c, nullptr, nullptr, nullptr, nullptr);
                        ante->right = nuevo;
                        nuevo->left = ante;
                        ante = nuevo;
                        if (c == '$') {
                            this->endGAME.push(1);//can de $
                        }
                        if (c == '@') {
                            this->jugador = nuevo; //Para saber donde esta el jugador siempre
                            this->jugador->punto = false;
                        }

                        if (c == ',') {
                            nuevo->setdata(' ');
                            nuevo->punto = false;
                        }
                        else {
                            nuevo->setdata(c);
                            if (c == '.') {
                                nuevo->punto = true;
                            }
                        }
                    }
                    else if (col == 0)
                    {
                        nuevo = priFila->down;
                        nuevo->setdata(c);
                        priFila = nuevo;
                        ante = nuevo;
                        if (c == '$') {
                            this->endGAME.push(1);//can de $
                        }
                        if (c == '@') {
                            this->jugador = nuevo; //Para saber donde esta el jugador siempre
                            this->jugador->punto = false;
                        }
                        if (c == ',') {
                            nuevo->setdata(' ');
                            nuevo->punto = false;
                        }
                        else {
                            nuevo->setdata(c);
                            if (c == '.') {
                                nuevo->punto = true;
                            }
                        }
                    }
                    else
                    {
                        nuevo = new Nodo(c, nullptr, nullptr, nullptr, nullptr);
                        ante->right = nuevo;
                        nuevo->left = ante;
                        ante = nuevo;
                        if (c == '$') {
                            this->endGAME.push(1);//can de $
                        }
                        if (c == '@') {
                            this->jugador = nuevo; //Para saber donde esta el jugador siempre
                            this->jugador->punto = false;
                        }

                        if (c == ',') {
                            nuevo->setdata(' ');
                            nuevo->punto = false;
                        }
                        else {
                            nuevo->setdata(c);
                            if (c == '.') {
                                nuevo->punto = true;
                            }
                        }
                    }
                }
                col++;
            }
        }
        //delete nuevo;
        priFila->down = new Nodo('x', priFila, nullptr, nullptr, nullptr);
        prifilaB = false;
        row++;
    }

    ante = this->inicio;
    Nodo* sig = this->inicio->down;
    Nodo* anteUNO = this->inicio;
    Nodo* sigUNO = this->inicio->down;
    row = 0;
    while (row - 1 < fil)
    {
        if (sig == nullptr) {
            break;
        }
        while (sig->right != nullptr)
        {
            ante->down = sig;
            sig->up = ante;
            ante = ante->right;
            sig = sig->right;
        }
        ante = sigUNO;
        sig = sigUNO->down;
        sigUNO = sig;
        row++;
    }
    archivo.close();
}

std::string Tabla::toString() {
    std::stringstream s;
    char cell = ' ';
    Nodo* aux = this->inicio;
    Nodo* actual = this->inicio;
    if (inicio != nullptr) {

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
                if (aux->down != nullptr) {
                    aux = aux->down;
                    actual = aux;
                }
            }
        }
    }
    return s.str();
}

std::string Tabla::movimientos()
{
    std::stringstream s;
    s << "===========================" << '\n';
    s << "  Controles de Movimiento  " << '\n';
    s << "===========================" << '\n';
    s << "-----------------------" << '\n';
    s << "  W: Mover Arriba" << '\n';
    s << "  A: Mover Izquierda" << '\n';
    s << "  D: Mover Derecha" << '\n';
    s << "  S: Mover Abajo" << '\n';
    s << "-----------------------" << '\n';
    s << "  ESC: Menu de pausa" << '\n';
    s << "-----------------------" << '\n';
    return s.str();
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


void Tabla::eliminarNodos()
{
    Nodo* actual = this->inicio;
    while (actual != nullptr)
    {
        Nodo* filaActual = actual;
        actual = actual->down; // Avanza a la siguiente fila
        while (filaActual != nullptr)
        {
            Nodo* nodoActual = filaActual;
            filaActual = filaActual->right; // Avanza al siguiente nodo en la misma fila
            delete nodoActual; // Libera la memoria del nodo actual
        }
    }
    this->inicio = nullptr;
}

Tabla* Tabla::restart()
{
    this->eliminarNodos();
    Tabla* nuevo = new Tabla(this->nomArchivo);
    return nuevo;
}

bool Tabla::guardar() {
    try {
        std::string nombreArchivo = "Guardado.txt";
        std::ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }
          
        Nodo* filaActual = this->inicio;
        while (filaActual != nullptr) {
            Nodo* nodoActual = filaActual;
            while (nodoActual != nullptr) {
                if (nodoActual->data == 'x') {
					break;
				}
                if (nodoActual->data == ' ') { 
                    archivo << ',';
                }
                else {
                    archivo << nodoActual->data;
                }
                nodoActual = nodoActual->right;
            }
            filaActual = filaActual->down;
            if (filaActual) {
                archivo << '\n';
            }
        }
        archivo.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al guardar los nodos: " << e.what() << std::endl;
        return false;
    }
}


std::string Tabla::getNombre()
{
    return nomArchivo;
}

Tabla::~Tabla()
{
	this->eliminarNodos();
}




