#ifndef SERVER_H
#define SERVER_H 

#include "commonAcceptorSocket.h"
#include <string>
#include <vector>

class Server {
	private:
		AcceptorSocket acceptor;
		//std::list<std::string> *answers;
		ProtectedCounter winners, losers;
		void printResults() const;
	public:
		explicit Server(std::vector<std::string> *answers);
		void bindAndListen(const char *port, int size);
		void run();
		bool isClosed() const;
		~Server();
};

#endif
