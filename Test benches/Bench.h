#pragma once
#include "..//Engine Simulation/Engine.h"

struct InformationPoint
{
private:
	float _power;
	float _ñrankshaftSpeed;
	size_t _time;
public:
	const float GetPower() { return _power; }

	const float GetCrankshaftSpeed() { return _ñrankshaftSpeed; }

	const size_t GetTime() { return _time; }
};

class Bench {
public:
	virtual void TestEngine(Engine engine) = 0;
};