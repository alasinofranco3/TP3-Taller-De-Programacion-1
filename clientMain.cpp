#include "client.h"

int main(int argc, char const *argv[]) {
	Client client;
	/*
	char message[] = "hola servidor";
	char buffer [32];
	*/

	//bool finish = false;
	
	if (argv[1] == NULL || argv[2] == NULL) {
		std::cout << "Error: argumentos invalidos." << std::endl;
		return ERROR;
	}
	client.connect(argv[1], argv[2]);
	client.run();
	

	/*
	client.send(message, 14);
	client.recv(buffer, 14);
	std::cout << buffer << std::endl;
	*/

	return 0;
}