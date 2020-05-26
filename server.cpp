#include "server.h"
#include <string>
#include <vector>

Server::Server(std::vector<std::string> *answers) {
	acceptor = AcceptorSocket(&winners, &losers, answers);
}

void Server::bindAndListen(const char *port, int size) {
	acceptor.bindAndListen(port, size);
}

void Server::run() {
	acceptor.start();
	//std::cout << "Lanzado thread aceptador" << std::endl;
	char command; 
	//std::cout << "ingrese un comando" << std::endl;
	std::cin >> command;
	while (command != 'q') {
		std::cin >> command;
	}
	//std::cout << "recibi una q procedo a terminar" << std::endl;
	acceptor.stop();
	acceptor.join();
	//std::cout << "Se joineo el aceptador correctamente" << std::endl;
	this->printResults();
}

void Server::printResults() const {
	std::cout << "Estadísticas:\n\tGanadores:  " << winners.get(); 
	std::cout << "\n\tPerdedores: " << losers.get() << std::endl;
}

bool Server::isClosed() const {
	return acceptor.isClosed();
}

Server::~Server() {}
