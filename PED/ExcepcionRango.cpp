#include "ExcepcionRango.h"

ExcepcionRango::ExcepcionRango(int min, int max)//constructo de excepciones de rango
{
	this->valorMaximo = max;
	this->valorMinimo = min;
}

ExcepcionRango::~ExcepcionRango() // destructor de excepciones de rango
{

}

std::string ExcepcionRango::toString() const // despliega un mensaje de error
{
	return "El dato ingresado no se encuentra dentro del rango...\n";
}
