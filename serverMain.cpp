#include "commonPeerClient.h"
#include "commonParser.h"
#include <arpa/inet.h>

//#include "commonProtocol.h"

#define LOSE_MESSAGE "PERDISTE"
#define LOSE_MESSAGE_LEN 8

int main(int argc, char const *argv[]) {
	Socket server;
	ProtectedCounter winners, losers;
	//char message[] = "GANASTE";
	//char buffer [32];
	
	//VERIFICO QUE LOS PARAMETROS PASADOS SEAN CORRECTOS
	if (argv[1] == NULL || argv[2] == NULL) {
		//SEGUN CONSIGNA DEBERIA IMPRIMIR POR LA SALIDA DE ERROR
		std::cout << "Error: argumentos invalidos." << std::endl;
		return ERROR;
	}

	
	//PROCESO DE PARSEO DE ARCHIVO DE NUMEROS Y CREACION DE LISTA DE POSIBLES RESPUESTAS
	std::list<std::string> answers;
	Parser parser(argv[2], &answers);
	if (parser.run() == ERROR) return ERROR;
	// FIN DE PROCESO

	//PROCESO DE COMUNICACION
	server.bindAndListen(argv[1], 1);
	PeerClient client(server.accept(), answers.front(), &winners, &losers);
	client.run();
	std::cout << "Estadísticas:​ \n\t​ Ganadores:  " << winners.get() << "\n\t​ Perdedores:​ ​" << losers.get() << std::endl;

	//bool finish = false;
	//int answer = stoi(answers.front());
	/*
	while (!finish) {
		char command [1];
		peerSkt.recv(command, 1);
		if (command[0] == 'h') {
			unsigned int helpMessageLen = strlen(MENSAJE_AYUDA);
			char *message = (char*)malloc(helpMessageLen + sizeof(int));
			strncpy(message + 4, MENSAJE_AYUDA, helpMessageLen);
			unsigned int *p = (unsigned int *)message;
			unsigned int helpMessageLenBig = htonl(helpMessageLen);
			*p = helpMessageLenBig;
			peerSkt.send(message, helpMessageLen + sizeof(int));
			free(message);
		} else if (command[0] == 's') {
			unsigned int surrenderMessageLen = LOSE_MESSAGE_LEN;
			char *message = (char*)malloc(LOSE_MESSAGE_LEN + sizeof(int));
			strncpy(message + 4, LOSE_MESSAGE, surrenderMessageLen);
			unsigned int *p = (unsigned int *)message;
			unsigned int surrenderMessageLenBig = htonl(surrenderMessageLen);
			*p = surrenderMessageLenBig;

			peerSkt.send(message, surrenderMessageLen + sizeof(int));
			free(message);

			finish = true;
		} else {
			char numberStr[2]; //Es de dos bytes
			peerSkt.recv(numberStr, 2);
			unsigned short int number = *(unsigned short int *)numberStr;
			number = ntohs(number);
			if (number < 100 || number > 999 || repeatedDigitNumber(number)) {
				
			}

		}	
	}
*/

	
	/*
	peerSkt.recv(buffer, 14);
	std::cout << buffer << std::endl;
	char messageLen [4];
	unsigned int* p = (unsigned int *)(messageLen);
	*p = 8;
	peerSkt.send(messageLen, 4);
	peerSkt.send(message, 14);
	*/
	//FIN DE PROCESO

	return 0;
}