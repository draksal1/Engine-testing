#pragma once
#include "Bench.h"

class PowerBench : Bench
{
private:
    double _timeStep;
    double _lastMaxPower;
    double _lastMaxRPM;
public:
    void TestEngine(Engine& engine) override;

    const double GetMaxPower() const;

    const double GetMaxRPM() const;
};

