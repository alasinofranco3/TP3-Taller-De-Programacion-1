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
	uint16_t number = protocol.recvNumber();
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
				(*winners)();
			} else {
				//Tengo sobrecargado el operador()
				//del protected counter para que incremente
				(*losers)();
			}	
		}	
	} else {
		protocol.sendString(NUMERO_INVALIDO);
	}
}

void PeerClient::run() {
	while (!finish) {
		char command [1];
		protocol.recvCommand(command);
		if (command[0] == 'h') {
			protocol.sendString("Comandos válidos:\n\tAYUDA: despliega la"
				" lista de comandos válidos\n\tRENDIRSE: pierde el juego "
				"automáticamente\n\tXXX: Número de 3 cifras a ser enviado "
				"al servidor para adivinar el número secreto");
		} else if (command[0] == 's') {
			protocol.sendString("Perdiste");
			finish = true;
			//Tengo sobrecargado el operador()
			//del protected counter para que incremente
			(*losers)();
		} else {
			this->processNumber();
		}
	}
	//deathState = true;
}

void PeerClient::stop() {
	finish = true;
}

PeerClient::~PeerClient() {}
