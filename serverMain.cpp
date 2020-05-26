#include "commonPeerClient.h"
#include "commonParser.h"
#include <arpa/inet.h>
#include "server.h"
#include "commonOSError.h"
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {	
	//VERIFICO QUE LOS PARAMETROS PASADOS SEAN CORRECTOS
	if (argv[1] == NULL || argv[2] == NULL) {
		std::cout << "Error: argumentos invalidos." << std::endl;
		return ERROR;
	}
	
	//PROCESO DE PARSEO DE ARCHIVO DE NUMEROS Y 
	//CREACION DE LISTA DE POSIBLES RESPUESTAS
	std::vector<std::string> answers;
	Parser parser(argv[2], &answers);
	if (parser.run() == ERROR) return ERROR;
	// FIN DE PROCESO

	//PROCESO DE COMUNICACION
	Server server(&answers);
	try {	
		server.bindAndListen(argv[1], 10);
		server.run();
	} catch(const OSError &e) {
		if (!server.isClosed()) {
			return ERROR;
		} 
	} catch(const std::exception &e) {
		return 1;
	}
	//FIN DE PROCESO

	return 0;
}
