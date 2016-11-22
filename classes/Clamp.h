#pragma once
#include "pch.h"

// Tool to keep values within certain range
class Clamp {
public:
	Clamp();
	~Clamp();

	template <typename T> static void ClampRange(T& value, T minRange, T maxRange) {

		if (value > maxRange) {
			Debug::Log("Value has been clamped to max range.");
			value = maxRange;
		}

		if (value < minRange) {
			Debug::Log("Value has been clamped to min range.");
			value = minRange;
		}
	}
};

