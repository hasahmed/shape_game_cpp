#include <chrono>
#include "shapegame.hpp"
using namespace shapegame;

Timer::Timer(
	double milliseconds,
	bool repeates,
	bool autoStart,
	std::function<void(void)> callBack,
	bool killOnComplete
) : Object(),
		milliseconds(milliseconds),
		repeates(repeates),
		autoStart(autoStart),
		callBack(callBack),
		killOnComplete(killOnComplete) {
			this->name = "Timer";
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
				if (this->killOnComplete)
					this->kill();
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