#include "commonPeerClient.h"
#include <string>
#include <utility>

PeerClient::PeerClient(Socket&& socket, std::string answer, 
	ProtectedCounter *w, ProtectedCounter *l) {
	this->protocol = std::move(Protocol(std::move(socket)));
	finish = false;
	tries = 10;
	this->answer = answer;
	winners = w;
	losers = l;
}

void PeerClient::processNumber() {
	tries --;
	unsigned short int number = protocol.recvNumber();
	if (protocol.validNumber(number)) {
		int correct = 0;
		int almost = 0;
		protocol.processNumber(number, answer, &correct, &almost);
		char result = protocol.processResults(correct, almost, tries);
		if (result == 'W' || result == 'L') {
			finish = true;
			if (result == 'W') {
				//Tengo sobrecargado el operador()
				//del protected counter para que incremente
				(*winners)(1);
			} else {
				//Tengo sobrecargado el operador()
				//del protected counter para que incremente
				(*losers)(1);
			}	
		}	
	} else {
		protocol.sendString(NUMERO_INVALIDO);
	}
}

void PeerClient::run() {
	while (!finish && !deathState) {
		char command [1];
		protocol.recvCommand(command);

		if (command[0] == 'h') {
			protocol.sendString("Comandos válidos:​ \n\t​AYUDA: despliega la"
			" lista de comandos válidos​ \n\t​RENDIRSE: pierde el juego "
			"automáticamente​ \n\t​XXX: Número de 3 cifras a ser enviado al "
			"servidor para adivinar el número secreto");
		} else if (command[0] == 's') {
			protocol.sendString("Perdiste");
			finish = true;
			//Tengo sobrecargado el operador()
			//del protected counter para que incremente
			(*losers)(1);
		} else {
			this->processNumber();
		}
	}
	deathState = true;
}

PeerClient::~PeerClient() {}
