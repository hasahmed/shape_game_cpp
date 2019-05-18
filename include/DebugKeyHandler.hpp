#pragma once
#include "Object.hpp"

namespace shapegame {
	class DebugKeyHandler : public Object {
		public: 
		DebugKeyHandler();
		void onKeyPress(Kb::Key key, Input::Action action) override;
	};
}