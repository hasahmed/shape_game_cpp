#pragma once
#include "Point.hpp"
namespace shapegame {
	struct RotationInfo {
		float nextRotation = 0.0f;
		float currentRotation = 0.0f;
		bool hasAlternateOrigin = false;
		Point alternateOrigin = { 0, 0 };
	};
}
