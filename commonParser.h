#ifndef COMMONPARSER_H
#define COMMONPARSER_H

#include <iostream>
#include <list>
#include <fstream>
#define ERROR 1

class Parser {
	private:
		std::list<std::string> *numbers;
		std::ifstream file;
		//Revisa si el numero pasado por parametro contiene todos sus digitos iguales
		bool sameDigitNumber(std::string number);
	public:
		Parser(std::string fileName, std::list<std::string> *answers);
		~Parser();
		int run();
	
};

#endif
