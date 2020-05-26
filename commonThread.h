#ifndef THREAD_H
#define THREAD_H 

#include <iostream>
#include <thread>
#include <unistd.h>
#include <atomic>

class Thread {
	private:
		std::thread thread;
	protected:
		std::atomic<bool> deathState;
	public:
		Thread();
        Thread(Thread&& other);
		void start();
		void join();
		void stop();
		virtual void run() = 0;
		virtual ~Thread();

		//Inhabilita las copias
	  	Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        //Habilita el movimiento
        Thread& operator=(Thread&& other);

        bool isDead() const;
};



#endif
