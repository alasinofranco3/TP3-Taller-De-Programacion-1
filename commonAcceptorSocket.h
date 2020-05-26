#ifndef COMMONACCEPTORSOCKET_H
#define COMMONACCEPTORSOCKET_H 

//#include "commonThread.h"
#include "commonProtectedCounter.h"
#include "commonPeerClient.h"
#include <atomic>
#include <algorithm>
#include <string>
#include <vector>

class AcceptorSocket : public Thread{
	private:
		std::atomic<bool> finish; // QUIZAS DEBERIA SER VARIABLE ATOMICA
		Socket skt;
		std::vector<Thread*> clients; // QUIZAS DEBERIAN SER THREADS
		std::vector<std::string> *answers;
		ProtectedCounter *winners, *losers;
	public:
		AcceptorSocket();
		AcceptorSocket(ProtectedCounter *w, ProtectedCounter *l, 
			std::vector<std::string> *answers);
		~AcceptorSocket();
		virtual void run() override;
		void bindAndListen(const char *port, int size);
		void close();
		bool isClosed() const;
		//Sobreescribo el operador igual para que me permita
		//copiar las referencias a los contadores y a la lista de
		//respuestas solamente.
		AcceptorSocket& operator=(const AcceptorSocket&);
};


#endif
