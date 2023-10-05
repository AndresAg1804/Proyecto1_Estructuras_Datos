#pragma once
#include<sstream>
#include<iostream>


class ExcepcionRango {
private:
	int valorMaximo;
	int valorMinimo;
public:
	ExcepcionRango(int, int);   // constructor
	virtual ~ExcepcionRango();  // desctructor
	std::string toString() const;    // toString
};

