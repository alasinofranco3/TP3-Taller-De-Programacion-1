#ifndef SERVER_H
#define SERVER_H 

#include "commonAcceptorSocket.h"
#include <string>
#include <vector>

class Server {
	private:
		AcceptorSocket acceptor;
		ProtectedCounter winners, losers;
		void printResults();
	public:
		explicit Server(std::vector<std::string> *answers);
		void bindAndListen(const char *port, int size);
		void run();
		bool isClosed() const;
		~Server();
};

#endif
