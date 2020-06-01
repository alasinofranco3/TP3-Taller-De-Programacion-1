#include "commonProtocol.h"
#include <string>
#include <utility>

Protocol::Protocol() {}

Protocol::Protocol(Socket&& socket) {
	skt = std::move(socket);
}

void Protocol::connect(const char  *host, const char  *port) {
	skt.connect(host, port);
}

bool Protocol::validCommand(const std::string command) const {
	try {
		if (command != "AYUDA" && command != "RENDIRSE" && 
			stoi(command) > (pow(2, 16) - 1)) {	
			//comparamos el comando con el numero maximo que podemos 
			//representar en 2 bytes, 2^16 - 1
			return false;
		}
		return true;
	} catch(const std::exception &e) {
		return false;
	}
}

bool Protocol::validNumber(uint16_t number) const{
	if (number < 100 || number > 999 || repeatedDigitNumber(number)) {
		return false;		
	}
	return true;
}

bool Protocol::repeatedDigitNumber(uint16_t number) const{
	int firstDigit, secondDigit, ThirdDigit;
	ThirdDigit = number % 10;
	number /= 10; 
	secondDigit = number % 10;
	number /= 10;
	firstDigit = number % 10;
	if (firstDigit == secondDigit || firstDigit == ThirdDigit 
		|| secondDigit == ThirdDigit) return true;
	return false;
}

void Protocol::sendCommand(const std::string command) const {
	if (command == "AYUDA") {
		skt.send("h", 1);
	} else if (command == "RENDIRSE") {
		skt.send("s", 1);
	} else {
		skt.send("n", 1);
		this->sendNumber(command);
	}
}

void Protocol::sendNumber(std::string command) const{
	//Paso el comando a entero
	uint16_t number = (uint16_t)stoi(command);
	number = htons(number); // Lo paso a big endian
	char message [2]; //1 byte para el comando y dos mas para el numero
	uint16_t* p = (uint16_t *)(message);
	*p = number;
	//Envio el numero
	skt.send(message, 2);
}

void Protocol::sendString(const char* string) const{
	uint32_t stringLen = strlen(string);
	//ademas del string se envia un int con su longitud
	char *message = (char*)malloc(stringLen + sizeof(int)); 
	strncpy(message + 4, string, stringLen);
	//Agregamos la longitud del string en big endian al mensaje
	uint32_t *p = (uint32_t *)message;
	uint32_t stringLenBigEndian = htonl(stringLen);
	*p = stringLenBigEndian;
	//enviamos el string
	skt.send(message, stringLen + sizeof(int));
	free(message);
}

void Protocol::recvCommand(char* buffer) const {
	skt.recv(buffer, 1); //El comando se envia en 1 byte
 }

uint16_t Protocol::recvNumber() const {
	char numberStr[2]; //Es de dos bytes
	skt.recv(numberStr, 2); //Los numeros vienen en 2 bytes
	char* aux = numberStr;
	 uint16_t number = *(uint16_t *)aux;
	//Lo paso a mi endianness local
	number = ntohs(number);
	return number;
}

uint32_t Protocol::recvStringSize() const{
	//El tamanio del string se pasa en un int de 4 bytes
	char messageSizeStr [4];
	skt.recv(messageSizeStr, 4);
	char* aux = messageSizeStr;
	uint32_t messageSize = *(uint32_t*)aux;
	//Lo paso all endianness local
	messageSize = ntohl(messageSize);
	return messageSize;
}

void Protocol::recvString(char* message, int size) const{
	skt.recv(message, size);
	message[size] = '\0';
}

void Protocol::processNumber(uint16_t number, 
	std::string answer, int* c, int *a) const {
	//Lo inicializo con 3 digitos cualesquiera,no tienen relevancia
	std::string digits = "abc";
	//voy guardando los digitos del numero en el string digits
	//en la pos 0 queda el digito mas significativo
	for (int i = 2; i >= 0; i--) {
		digits[i] = (char)((number % 10) + 48);
		number /= 10; 
	}
	//Voy comparando los dijistos del numero ingresado con los
	//digitos de la respuesta
	for (int i = 0; i < 3; i ++) {
		if (digits[i] == answer[i]) {
			(*c) ++;
		} else if (answer.find_first_of(digits[i]) != std::string::npos) {
			(*a) ++;
		}
	}
}

char Protocol::processResults(int correct, int almost, const int tries) const {
	//A los enteros les sumo 48 para agregar al mensaje el simbolo ascii 
	//correspondiente a su valor numerico

	std::stringstream message;
	if (correct == 3) {
		this->sendString("Ganaste");
		return 'W';
	} else if (correct > 0 && almost > 0) {
		message << correct << " bien, " << almost << " regular";
	} else if (correct > 0) {
		message << correct << " bien";
	} else if (almost > 0) {
		message << almost << " regular";
	} else {
		message << "3 mal";
	}

	if (tries > 0) {
		std::string aux = message.str();
		this->sendString(aux.c_str());
		return 'N';
	} else {
		this->sendString("Perdiste");
		return 'L';
	}
}

Protocol::~Protocol() {}

Protocol& Protocol::operator=(Protocol&& other) {
	this->skt = std::move(other.skt);
    return *this;
}

void Protocol::stop() {
	skt.shutDown();
	skt.close();
}
