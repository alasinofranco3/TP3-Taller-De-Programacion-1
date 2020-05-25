#ifndef COMMONPEERCLIENT_H
#define COMMONPEERCLIENT_H 

#include "commonThread.h"
#include "commonProtocol.h"
#include "commonProtectedCounter.h"


#define MENSAJE_AYUDA "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número de 3 cifras a ser enviado al servidor para adivinar el número secreto"
#define NUMERO_INVALIDO "Número inválido. Debe ser de 3 cifras no repetidas"

class PeerClient : public Thread {
	private:
		Protocol protocol;
		//bool finish;
		int tries;
		std::string answer;
		ProtectedCounter *winners, *losers;
	public:
		PeerClient(Socket&& socket, std::string answer, 
			ProtectedCounter *w, ProtectedCounter *l);
		virtual void run() override;
		~PeerClient();
	
};

#endif
