#include "commonThread.h"
#include <utility>

Thread::Thread() {
	deathState = false;
}

Thread::Thread(Thread&& other) {
	this->thread = std::move(other.thread);
}

void Thread::start() {
	thread = std::thread(&Thread::run, this);
	deathState = true;
}

void Thread::join() {
    thread.join();
}

Thread& Thread::operator=(Thread&& other) {
	this->thread = std::move(other.thread);
    return *this;
}

bool Thread::isDead() const {
	return deathState;
}

Thread::~Thread() {}
