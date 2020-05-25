#ifndef THREAD_H
#define THREAD_H 

#include <iostream>
#include <thread>
#include <unistd.h>

class Thread {
	private:
		std::thread thread;

	public:
		Thread();
        Thread(Thread&& other);
		void start();
		void join();
		virtual void run() = 0;
		virtual ~Thread();

		//Inhabilita las copias
	  	Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        //Habilita el movimiento
        Thread& operator=(Thread&& other);
};



#endif
