#ifndef CLIENT_H
#define CLIENT_H

#include "commonProtocol.h"

class Client {
	private: 
		Protocol protocol;
		bool finish;
	public:
		Client();
		~Client();
		void connect(const char *host, const char  *port);
		void run();
	
};

#endif
