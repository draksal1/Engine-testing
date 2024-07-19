#pragma once
#include "..//Engine Simulation/Engine.h"

// Abstract class, added for scalling
class Bench {
public:
	virtual void TestEngine(Engine& engine) = 0;
};