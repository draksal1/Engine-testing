#pragma once
#include "Bench.h"

// Class for conducting an overheating time test
class TemperatureBench : public Bench {
private:
    double _lastOverheatingTime;
    double _timeStep;

public:
    TemperatureBench(double timeStep) : _timeStep(timeStep), _lastOverheatingTime(0.0) {}

    void TestEngine(Engine& engine) override;

    const double GetOverheatingTime() const;
};

