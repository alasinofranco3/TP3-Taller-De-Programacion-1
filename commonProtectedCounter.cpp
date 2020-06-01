#include "commonProtectedCounter.h"

ProtectedCounter::ProtectedCounter() {
	counter = 0;
}	
/*
void ProtectedCounter::add(const int value) {
	std::unique_lock<std::mutex> lk(mutex);	
	counter += value;
}
*/

void ProtectedCounter::operator()() {
	std::unique_lock<std::mutex> lk(mutex);	
	counter ++;
}

void ProtectedCounter::print() {
	std::unique_lock<std::mutex> lk(mutex);	
	std::cout << "Puntos de Beneficio acumulados: " << counter << std::endl;
}

int ProtectedCounter::get() {
	std::unique_lock<std::mutex> lk(mutex);	
	return counter;
}

ProtectedCounter::~ProtectedCounter() {}
