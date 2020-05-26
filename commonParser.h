#ifndef COMMONPARSER_H
#define COMMONPARSER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define ERROR 1

class Parser {
	private:
		std::vector<std::string> *numbers;
		std::ifstream file;
		//Revisa si el numero pasado por parametro contiene todos sus digitos iguales
		bool sameDigitNumber(std::string number);
	public:
		Parser(std::string fileName, std::vector<std::string> *answers);
		~Parser();
		int run();
};

#endif
