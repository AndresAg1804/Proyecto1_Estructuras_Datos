#include "Tabla.h"
#include <cstdlib>

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

        this->matrix = new Nodo ** [this->fil];
        for (int i = 0; i < this->fil; i++) {
            this->matrix[i] = new Nodo*[this->col];
        }

        for (int i = 0; i < this->fil; i++) {
            for (int j = 0; j < this->col; j++) {
                this->matrix[i][j] = new Nodo('.',nullptr, nullptr, nullptr, nullptr);
            }
        }


        this->inicio = this->matrix[0][0];

        for (int i = 0; i < fil; i++) {
            for (int j = 0; j < col; j++) {
                if (i > 0) {
                    this->matrix[i][j]->up = this->matrix[i - 1][j];
                }

                if (i < fil - 1) {
                    this->matrix[i][j]->down = this->matrix[i + 1][j];
                }

                if (j > 0) {
                    this->matrix[i][j]->left = this->matrix[i][j - 1];
                }

                if (j < col - 1) {
                    this->matrix[i][j]->right = this->matrix[i][j + 1];
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

                    if (c == '@') {
                        this->jugador = this->matrix[row][col]; //Para saber donde esta el jugador siempre
                    }

                    if (c == ',') {
                        this->matrix[row][col]->setdata(' ');
                    }
                    else {
                        this->matrix[row][col]->setdata(c);
                    }

                    col++;
                }
            }
            row++;
        }
        archivo.close();
        /// ////////////////////////////////////////////////////////////////////////////////
        
}


std::string Tabla::toString()
{
    std::stringstream s;
    this->jugador->up->setdata('8');
    this->jugador->right->setdata('8');
    this->jugador->left->setdata('8');
    this->jugador->down->setdata('8');
    for (int i = 0; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << this->matrix[i][j]->data;
        }
        std::cout << '\n';
    }
	return s.str();
}


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


