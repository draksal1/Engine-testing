#pragma once
#include "Bench.h"

// Class for maximum power test
class PowerBench : Bench
{
private:
    double _timeStep;
    double _lastMaxPower;
    double _lastMaxRPM;
public:
    PowerBench(double timeStep) : _timeStep(timeStep), _lastMaxPower(0.0), _lastMaxRPM(0.0) {}

    void TestEngine(Engine& engine) override;

    const double GetMaxPower() const;

    const double GetMaxRPM() const;
};

