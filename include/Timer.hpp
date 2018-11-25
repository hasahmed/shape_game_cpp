#include <chrono>
#include <functional>
namespace shapegame {
	class Timer : public Object {
		private:
			int milliseconds;
			bool repeates;
			bool autoStart;
			// std::function<void()> callBack;
			std::function<void(void)> callBack;
			// void (Object::*callBack)(void);

			// Object &callingInst;

			// internal state	
			bool _running = false;
			// int _timeLeft;
			std::chrono::time_point<std::chrono::high_resolution_clock> _timerStart;
			std::chrono::duration<double> _timeElapsed;
			// std::chrono::time_point<std::chrono::high_resolution_clock> _end;
			// std::chrono::time_point<std::chrono::high_resolution_clock> _timerLeft;

		public:
			Timer(double seconds, bool repeates, bool autoStart, std::function<void(void)> callBack);
			void start();
			void stop();
			void onAdd() override;
			void update() override;
	};
}