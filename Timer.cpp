#include <chrono>
#include "shapegame"
using namespace shapegame;

Timer::Timer(
	int milliseconds,
	bool repeates,
	bool autoStart,
	// void (HeadNode::*callBack)(void),
	// void (Object::*callBack)(void),
	std::function<void(void)> callBack
	// Object &callingInst
) : Object(), milliseconds(milliseconds), repeates(repeates), autoStart(autoStart), callBack(callBack) {
// ) : Object(), milliseconds(milliseconds), repeates(repeates), autoStart(autoStart), callBack(callBack), callingInst(callingInst) {
	// this->callBack = std::bind(&callBack, this);
	// std::function<void(void)> f = std::bind(&callBack, this);
}
void Timer::onAdd() {
	if (this->autoStart) {
		this->start();
	}
}
void Timer::update() {
	if (this->_running) {
		this->_timeElapsed += std::chrono::high_resolution_clock::now() - this->_timerStart;
		if (this->_timeElapsed.count() >= milliseconds) {
			this->callBack();
			if (!this->repeates) {
				puts("Need to write code to remove objects");
			} else {
				this->_timeElapsed -= this->_timeElapsed;
				this->_timerStart = std::chrono::high_resolution_clock::now();
			}
		}
	}
}

void Timer::start() {
	this->_timerStart = std::chrono::high_resolution_clock::now();
	this->_running = true;
}

void Timer::stop() {
	this->_running = false;
}