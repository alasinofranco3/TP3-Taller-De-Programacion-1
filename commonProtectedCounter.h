#ifndef COMMONPROTECTEDCOUNTER_H
#define COMMONPROTECTEDCOUNTER_H 

#include <mutex>
#include <iostream>

class ProtectedCounter {
	private:
		std::mutex mutex;
		int counter;
	public:
		ProtectedCounter();
		~ProtectedCounter();
		void add(const int value);
		void print() const;
		int get() const;
};

#endif
