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
		std::vector<Thread*> clients; // QUIZAS DEBERIAN SER THREADS
		std::vector<std::string> *answers;
		Socket skt;
		ProtectedCounter *winners, *losers;
	public:
		AcceptorSocket();
		AcceptorSocket(ProtectedCounter *w, ProtectedCounter *l, 
			std::vector<std::string> *answers);
		~AcceptorSocket();
		void bindAndListen(const char *port, int size);
		bool isClosed() const;
		virtual void stop() override;
		virtual void run() override;
		//Sobreescribo el operador igual para que me permita
		//copiar las referencias a los contadores y a la lista de
		//respuestas solamente.
		AcceptorSocket& operator=(const AcceptorSocket&);
};


#endif
