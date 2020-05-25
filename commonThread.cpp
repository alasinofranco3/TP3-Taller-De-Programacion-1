#include "commonThread.h"
#include <utility>

Thread::Thread() {}

Thread::Thread(Thread&& other) {
	this->thread = std::move(other.thread);
}

void Thread::start() {
	thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread& Thread::operator=(Thread&& other) {
	this->thread = std::move(other.thread);
    return *this;
}

Thread::~Thread() {}
