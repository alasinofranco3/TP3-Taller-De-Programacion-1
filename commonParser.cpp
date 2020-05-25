#include "commonParser.h"

Parser::Parser(std::string fileName, std::list<std::string> *answers) {
	file.open(fileName);
	numbers = answers;
}

int Parser::run() {
	std::string line;
	int number;

	if (!file.good()) {
		std::cout << "Error al abrir el archivo de numeros\n";
		return ERROR;
	}

	while (std::getline(file, line)) {
		if (sameDigitNumber(line)) {
			//SEGUN CONSIGNA DEBERIA IMPRIMIR POR LA SALIDA DE ERROR
			std::cout<<"Error: formato de los números inválidos"<<std::endl;
			return ERROR;
		}
		number = std::stoi(line);
		if (number < 100 || number > 999) {
			//SEGUN CONSIGNA DEBERIA IMPRIMIR POR LA SALIDA DE ERROR
			std::cout <<"Error: archivo con números fuera de rango"<<std::endl;
			return ERROR;
		}
		numbers->push_back(line);
	}
	return 0;
}

bool Parser::sameDigitNumber(std::string number) {
	bool result = false;
	for (unsigned int i = 0; i < number.size() && result == false; i++) {
		for (unsigned int j = 0; j < number.size() && result == false; j++) {
			if (number[i] == number[j] && i != j) {
				result = true;
			}	
		}	
	}

	return result;
}

Parser::~Parser() {
	file.close();
}