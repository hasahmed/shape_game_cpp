#pragma once

namespace shapegame {
	class Dirtyable {
		public:
			virtual void dirty() = 0;
	};
}