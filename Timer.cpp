#include <chrono>
#include "shapegame"
using namespace shapegame;

Timer::Timer(
	double seconds,
	bool repeates,
	bool autoStart,
	std::function<void(void)> callBack
) : Object(), milliseconds(seconds), repeates(repeates), autoStart(autoStart), callBack(callBack) {
}
void Timer::onAdd() {
	if (this->autoStart) {
		this->start();
	}
}
void Timer::update() {
	if (this->_running) {
		this->_timeElapsed += std::chrono::high_resolution_clock::now() - this->_timerStart;
		std::cout << this->_timeElapsed.count() << std::endl;
		if (this->_timeElapsed.count() >= this->milliseconds) {
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