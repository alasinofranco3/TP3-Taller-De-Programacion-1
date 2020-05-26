#include "commonAcceptorSocket.h"
#include "commonOSError.h"
#include <vector>
#include <string>
#include <utility>

AcceptorSocket::AcceptorSocket() {
	finish = false;
}

AcceptorSocket::AcceptorSocket(ProtectedCounter *w, ProtectedCounter *l, 
	std::vector<std::string> *answers) {
	//finish = false;
	winners = w; 
	losers = l; 
	this->answers = answers;
}
void AcceptorSocket::bindAndListen(const char *port, int size) {
	skt.bindAndListen(port, size);
}

void AcceptorSocket::run() {
	unsigned int index = 0;

	while (!finish) {
	//std::cout << "aceptador debe terminar? "<< finish << std::endl;
		//Socket peerSkt = skt.accept();
		std::string answer = answers->at(index);
		//std::cout << "esperando aceptar un cliente" << std::endl;
		try {
			Socket clientSkt = skt.accept(); //PUEDE FALLAR VER QUE HACER EN ESE CASO
			//std::cout << "Acpete un cliente" << std::endl;
			Thread *t = new PeerClient(std::move(clientSkt), answer, winners, losers);
			t->start();
			//std::cout << "Lance el peer client" << std::endl;
			clients.push_back(t);

			index ++;
			if (index == answers->size()) {
				index = 0;
			}

			std::vector<Thread*> tmp;
			for (unsigned int i = 0; i < clients.size(); i++) {
				if (clients[i]->isDead()) {
					clients[i]->join();
					delete clients[i];
				} else {
					tmp.push_back(clients[i]);
				}
			}
			clients.swap(tmp);
		} catch(const OSError &e) {
			if (!finish) {
				throw OSError("Error del socket al aceptar un cliente");
			} 
		}
	}

	for (unsigned int i = 0; i < clients.size(); i++) {
		clients[i]->join();
		delete clients[i];
	}
	//std::cout << "aceptador termino de correr" << std::endl;	
}

void AcceptorSocket::close() {
	finish = true;
	skt.shutDown();
	skt.close();
}

bool AcceptorSocket::isClosed() const {
	return finish;
}

AcceptorSocket& AcceptorSocket::operator=(const AcceptorSocket& other) {
	winners = other.winners;
	losers = other.losers;
	answers = other.answers;
	return *this;
}

AcceptorSocket::~AcceptorSocket() {}
