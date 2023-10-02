#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include <cstdlib>

class Tabla {
public:
    struct Nodo {
        char data;
        struct Nodo* up;
        struct Nodo* down;
        struct Nodo* left;
        struct Nodo* right;
        Nodo(char dat = '.', Nodo* u = nullptr, Nodo* d = nullptr, Nodo* l = nullptr, Nodo* r = nullptr) :data{ dat }, up{ u }, down{ d }, left{ l }, right{ r } {}
        void setdata(char dd) { data = dd; };
    };
    //falta la Pila para simluar un contador de "$"
    int col;
    int fil;
    Nodo*** matrix;
    int leerCol(const std::string& nombreArchivo);
    int leerfil(const std::string& nombreArchivo);
    Nodo* inicio;
    Nodo* jugador;
	Tabla(const std::string& nombreArchivo);
	std::string toString();
    void START();
    int getMove();
};