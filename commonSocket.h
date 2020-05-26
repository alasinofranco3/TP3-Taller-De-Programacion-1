#ifndef COMMONSOCKET_H
#define COMMONSOCKET_H

#include <string>
#include <iostream>
#include <cstring>


#define ERROR 1

class Socket {
	private:
		int skt;
		void set_TCP_options(struct addrinfo *hints);
		void error_in_getaddrinfo(int status, Socket *skt); 
		explicit Socket(int skt);
	
	public:
		Socket();
		~Socket();
		
		/* Size es la cantidad de clientes que podra teneer 
		en espera el skt_aceptador */
		void bindAndListen(const char *port, int size);

		void connect(const char  *host, const char  *port);

		Socket accept();

		/*Reactiva una direccion en caso de que esta estuviese en TIME WAIT */
		void reset();

		//void shutDown();

		/*Devuelve 0 en caso de exito o ERROR en caso de error.*/
		int send(const char *message, int len) const;

		/* Esta funcion recibe datos hasta que se llene el buffer o
		hasta que se cierre el socket remoto.
		La funcion devuelve 0 en caso de que se cierre el socket remoto
		,ERROR en caso de error o los caracteres recibidos en otro caso. */
		int recv(char *buffer, int size) const;

		void shutDown();
		void close();

		//Inhabilita las copias
	  	Socket(const Socket &copy) = delete;
        Socket& operator=(const Socket &copy) = delete;

        //Habilita el movimiento
        Socket(Socket &&other) noexcept;
        Socket& operator=(Socket &&other);
};

#endif
