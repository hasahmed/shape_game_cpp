#include <chrono>
#include <functional>
namespace shapegame {
	class Timer : public Object {
		private:
			double milliseconds;
			bool repeates;
			bool autoStart;
			std::function<void(void)> callBack;
			bool killOnComplete;

			// internal state	
			bool _running = false;
			std::chrono::time_point<std::chrono::high_resolution_clock> _timerStart;
			std::chrono::duration<double> _timeElapsed {0};
			std::chrono::milliseconds _msElapsed {0};

		public:
			Timer(double millisecs, bool repeates, bool autoStart, std::function<void(void)> callBack, bool killOnComplete=true);
			~Timer() = default;
			void start();
			void stop();
			void onAdd() override;
			void update() override;
	};
}