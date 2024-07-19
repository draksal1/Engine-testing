#include "TemperatureBench.h"


void TemperatureBench::TestEngine(Engine& engine){
    engine.StartEngine();
    double LastTemperature = engine.GetTemperature();
    double time = 0.0;
   
    while (engine.GetTemperature() <= engine.GetOverheatTemperature()) {
        engine.UpdateState(_timeStep);
        time += _timeStep;
        if (LastTemperature >= engine.GetTemperature())
        {
            engine.StopEngine();
            throw std::runtime_error("Engine cooling");
        }
        LastTemperature = engine.GetTemperature();
    }

    engine.StopEngine();
    _lastOverheatingTime = time;
}

const double TemperatureBench::GetOverheatingTime() const {
    return _lastOverheatingTime;
}