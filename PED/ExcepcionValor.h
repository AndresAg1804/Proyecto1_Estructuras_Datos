#pragma once
#include<sstream>
#include<iostream>


class ExcepcionValor {
public:
	ExcepcionValor();  // constructor
	virtual ~ExcepcionValor();  // destructor
	std::string toString() const;  // toString
};

