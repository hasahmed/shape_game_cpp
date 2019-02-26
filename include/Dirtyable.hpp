#pragma once

namespace shapegame {
	class Dirtyable {
		public:
			virtual void setDirty(bool dirty) = 0;
			virtual bool isDirty() = 0;
			virtual ~Dirtyable() = default;
	};
}