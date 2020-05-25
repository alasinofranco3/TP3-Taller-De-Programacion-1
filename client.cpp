#include "client.h"

Client::Client() {
	finish = false;
}

void Client::connect(const char *host, const char  *port) {
	protocol.connect(host, port);
}

void Client::run() {
	while (!finish) {
		std::string command;
		std::cout << "Ingrese un comando" << std::endl;
		std::cin >> command;
		
		if (protocol.validCommand(command)) {
			//enviar al servidor el comando adecuado
			protocol.sendCommand(command);
			//recibir respuesta del servidor
			unsigned int messageSize = protocol.recvStringSize();
			char *message = (char*)malloc(messageSize + 1);
			protocol.recvString(message, messageSize);
			std::cout << message << std::endl;
			if (strcmp(message, "GANASTE") == 0 || strcmp(message, "PERDISTE") == 0) {
				finish = true;
			}
			free(message);
		} else {
			std::cout << "Error: comando inválido. Escriba AYUDA para obtener ayuda" << std::endl;
		}

	}
}

Client::~Client() {}