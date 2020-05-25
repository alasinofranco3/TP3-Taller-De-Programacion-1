#ifndef COMMONPROTOCOL_H
#define COMMONPROTOCOL_H 

#include <string>
#include <cmath>
#include <iostream>
#include <arpa/inet.h>
#include "commonSocket.h"

class Protocol {
	private:
		Socket skt;
		bool repeatedDigitNumber(unsigned short int number);
	public:
		Protocol();
		Protocol(Socket&& socket);
		~Protocol();
		void connect(const char  *host, const char  *port);
		bool validCommand(const std::string command) const;
		bool validNumber(unsigned short int number);
		void sendCommand(const std::string command) const; 
		void sendString(const char* string);
		void recvCommand(char* buffer);
		unsigned short int recvNumber();
		unsigned int recvStringSize() const;
		void recvString(char* message, int size) const;
		void processNumber(unsigned short number, std::string answer, 
			int* c, int *a) ;
		
		//Devuelve 'W' en caso de que haya acertado el numero o 'N'
		//si no lo hizo;
		char processResults(int correct, int almost, const int tries);
		
		Protocol& operator=(Protocol &&other);
	
	
};

#endif
