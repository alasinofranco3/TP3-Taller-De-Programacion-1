#ifndef COMMONPEERCLIENT_H
#define COMMONPEERCLIENT_H 

#include "commonThread.h"
#include "commonProtocol.h"
#include "commonProtectedCounter.h"
#include <string>

#define NUMERO_INVALIDO "Número inválido. Debe ser de 3 cifras no repetidas"

class PeerClient : public Thread {
	private:
		Protocol protocol;
		bool finish;
		int tries;
		std::string answer;
		ProtectedCounter *winners, *losers;
		void processNumber();

	public:
		PeerClient(Socket&& socket, std::string answer, 
			ProtectedCounter *w, ProtectedCounter *l);
		virtual void run() override;
		virtual void stop() override;
		~PeerClient();
};

#endif
