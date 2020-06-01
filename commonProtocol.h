#ifndef COMMONPROTOCOL_H
#define COMMONPROTOCOL_H 

#include <cmath>
#include <iostream>
#include <arpa/inet.h>
#include "commonSocket.h"
#include <string>
#include <sstream>

class Protocol {
	private:
		Socket skt;
		//Verifica si el numero pasado tiene digitos repetidos
		bool repeatedDigitNumber(uint16_t number) const;
		void sendNumber(std::string command) const;
	
	public:
		Protocol();
		explicit Protocol(Socket&& socket);
		~Protocol();
		void connect(const char  *host, const char  *port);
		//Verifica si el comando pasado es valido
		bool validNumber(uint16_t number) const;
		bool validCommand(const std::string command) const;
		void sendCommand(const std::string command) const; 
		void sendString(const char* string) const;
		void recvCommand(char* buffer) const;
		uint16_t recvNumber() const;
		uint32_t recvStringSize() const;
		void recvString(char* message, int size) const;
		void processNumber(uint16_t number, std::string answer, 
			int* c, int *a) const;
		
		//Devuelve 'W' en caso de que haya acertado el numero o 'N'
		//si no lo hizo y 'L' si el jugador perdio;
		//Ademas envia el mensaje correspondiente
		char processResults(int correct, int almost, const int tries) const;
		Protocol& operator=(Protocol &&other);
		void stop();
};

#endif
