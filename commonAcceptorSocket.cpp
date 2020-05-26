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
		std::string answer = answers->at(index);
		try {
			Socket clientSkt = skt.accept();
			Thread *t = new PeerClient(std::move(clientSkt), answer, winners, losers);
			t->start();
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
}

void AcceptorSocket::stop() {
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
