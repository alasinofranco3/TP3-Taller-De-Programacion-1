#define _POSIX_C_SOURCE 200112L 
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "commonSocket.h"
#include "commonOSError.h"

//FUNCIONES PRIVADAS
void Socket::error_in_getaddrinfo(int status, Socket *skt) {
	if (status != 0) { 
		//MENSAJE AGREGARLO AL LANZAR LA EXCEPCION CREADA  		
  		//printf("Error in getaddrinfo: %s\n", gai_strerror(status));
      	throw OSError("Error en getaddrinfo: %s\n", gai_strerror(status));
   	}
}

void Socket::set_TCP_options(struct addrinfo *hints) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = 0;
}


//FUNCIONES PUBLICAS
Socket::Socket() {
	struct addrinfo hints;
	set_TCP_options(&hints);
	
	skt = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);

	if (skt == -1) {
		//printf("Error in socket():%s\n", std::strerror(errno));
		throw OSError("Error en cosntructor del socket");
	}	
}


Socket::Socket(int skt) {
	this->skt = skt;
}

Socket::~Socket() {
	if (skt != -1) {
		shutdown(skt, SHUT_RDWR);
		::close(skt);
	}
	skt = -1;
}

Socket::Socket(Socket&& other) noexcept: skt(other.skt) {
	other.skt = -1;
}

Socket& Socket::operator=(Socket&& other) {	
	this->skt = std::move(other.skt);
	other.skt = -1;
    return *this;
}

void Socket::bindAndListen(const char *port, int size) {
	int status;
	struct addrinfo *results, *ptr;
	struct addrinfo hints;
	bool success = false;

	//RESETEAMOS EL SOCKET POR SI ESTUVIESE EN TIME WAIT
	this->reset();

	set_TCP_options(&hints);
	
	status = getaddrinfo(NULL, port, &hints, &results);

	//VERIFICO SI HUBO ERROR EN EL GETADRRINFO
	error_in_getaddrinfo(status, this);

	for (ptr = results; ptr != NULL && success == false; ptr = ptr->ai_next) {
		status = ::bind(skt, ptr->ai_addr, ptr->ai_addrlen);
		status = ::listen(skt, size);
		success = (status != -1);
	}

	freeaddrinfo(results);
	
	if (success == false) {
		//MENSAJE AGREGARLO AL LANZAR LA EXCEPCION CREADA
		OSError("Error en bindAndListen(), se acabaron las direcciones validas");
	}	
}

void Socket::reset() {
	int status;
	int val = 1;
	status = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (status == -1) {
		//MENSAJE AGREGARLO AL LANZAR LA EXCEPCION CREADA
		//printf("Error in reset: %s\n", strerror(errno));
    	throw OSError("Error al resetear la direccion del socket");
    }
}

void Socket::connect(const char *host, const char *port) {
	int status = 0;
	bool connected = false;
	struct addrinfo *results, *ptr;
	struct addrinfo hints;

	set_TCP_options(&hints);

	status = getaddrinfo(host, port, &hints, &results);

	//VERIFICO SI HUBO ERROR EN EL GETADRRINFO
	error_in_getaddrinfo(status, this);

	for (ptr = results; ptr != NULL && connected == false; ptr = ptr->ai_next) {
		// NO HACE FALTA CREAR EL SOCKET ACA PORQUE YA LO TENEMOS CREADO
		//DESDE ANTES USANDO LAS MISMAS HINTS QUE RESULT
		status = ::connect(skt, ptr->ai_addr, ptr->ai_addrlen);
		//NO CHEQUEAMOS SI HAY ERROR YA QUE TODAVIA PODRIAMOS 
		//CONECTARNOS CON LAS DIRECCIONES SIGUIENTES
		connected = (status != -1);
	}

	freeaddrinfo(results);

	if (connected == false) {
		throw OSError("No se pudo conectar el socket, "
			"se acabaron las direcciones validas");
	}
}

Socket Socket::accept() {
	int auxSkt;
	auxSkt = ::accept(skt, nullptr, nullptr);

	if (auxSkt == -1) {
		//printf("Error in accept: %s\n", strerror(errno));
    	throw OSError("Error del socket al aceptar un cliente");
	}

	return std::move(Socket(auxSkt));
}


int Socket::send(const char *message, int len) const {
	int sent = 0;
	int result; 
	bool remote_skt_closed = false;

	while (remote_skt_closed == false && sent < len) {
		result = ::send(skt, &message[sent], (len - sent), MSG_NOSIGNAL);
		
		if (result == 0) {  //SI RESULT VALE CERO NOS CERRARON EL SKT
			remote_skt_closed = true;
		} else if (result == -1) {
			//printf("Error in send: %s\n", strerror(errno));
			throw OSError("Error al enviar a traves del socket");
		} else {
			sent += result;
		}
	}
	
	if (remote_skt_closed) return 0;
	return sent;
}

int Socket::recv(char *buffer, int size) const {
	//std::cout << "Recibiendo del skt" << skt << std::endl;
	int received = 0;
	int result;
	bool skt_closed = false;

	while (received < size && skt_closed == false) {
		result = ::recv(skt, &buffer[received], (size - received), 0);
		if (result == -1) {
			//printf("Error in recv: %s\n", strerror(errno));
    		throw OSError("Error al recibir a traves del socket");
		} else if (result == 0) { //SI received VALE CERO NOS CERRARON EL SKT
			skt_closed = true;
		} else {
			received += result;
		}
	}
	
	if (skt_closed) return 0; 
	return received;
}

void Socket::close() {
	std::cout << "cerrando el acceptador" << std::endl;
	::close(skt);	
}

void Socket::shutDown() {
	shutdown(skt, SHUT_RDWR);
}
