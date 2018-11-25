#include <chrono>
#include <functional>
namespace shapegame {
	class Timer : public Object {
		private:
			int milliseconds;
			bool repeates;
			bool autoStart;
			std::function<void(void)> callBack;

			// internal state	
			bool _running = false;
			std::chrono::time_point<std::chrono::high_resolution_clock> _timerStart;
			std::chrono::duration<double> _timeElapsed;

		public:
			Timer(double seconds, bool repeates, bool autoStart, std::function<void(void)> callBack);
			void start();
			void stop();
			void onAdd() override;
			void update() override;
	};
}