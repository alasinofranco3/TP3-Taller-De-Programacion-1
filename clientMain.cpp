#include "client.h"

int main(int argc, char const *argv[]) {
	Client client;
	
	if (argv[1] == NULL || argv[2] == NULL) {
		std::cout << "Error: argumentos invalidos." << std::endl;
		return ERROR;
	}
	client.connect(argv[1], argv[2]);
	client.run();

	return 0;
}
