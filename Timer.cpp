#include <chrono>
#include "shapegame"
using namespace shapegame;

Timer::Timer(
	double milliseconds,
	bool repeates,
	bool autoStart,
	std::function<void(void)> callBack
) : Object(), milliseconds(milliseconds), repeates(repeates), autoStart(autoStart), callBack(callBack) {
}
void Timer::onAdd() {
	if (this->autoStart) {
		this->start();
	}
}
void Timer::update() {
	if (this->_running) {
		this->_msElapsed =
			std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::high_resolution_clock::now() - this->_timerStart
			);
		if (this->_msElapsed.count() >= this->milliseconds) {
			this->callBack();
			if (!this->repeates) {
				this->_running = false;
				puts("Need to write code to remove objects");
			} else {
				this->start();
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