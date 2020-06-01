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
	char command; 
	std::cin >> command;
	while (command != 'q') {
		std::cin >> command;
	}
	acceptor.stop();
	acceptor.join();
	this->printResults();
}

void Server::printResults()  {
	std::cout << "Estadísticas:\n\tGanadores:  " << winners.get(); 
	std::cout << "\n\tPerdedores: " << losers.get() << std::endl;
}

bool Server::isClosed() const {
	return acceptor.isClosed();
}

Server::~Server() {}
