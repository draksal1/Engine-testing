#include "PowerBench.h"

void PowerBench::TestEngine(Engine& engine){
    engine.StartEngine();
    double maxPower = 0.0;
    double maxRPM = 0.0;
    double lastRPM = -1;
    double currentPower = 0.0;


    while (true) {
        engine.UpdateState(_timeStep);
        double currentPower = engine.GetPower();
        double currentRPM = engine.GetRPM();

        // Power started to drop or went on the shelf
        if (currentPower <= maxPower) {
            engine.StopEngine();
            break;
        }

        if (currentPower > maxPower) {
            maxPower = currentPower;
            maxRPM = currentRPM;
        }

        lastRPM = currentRPM;
    }

    _lastMaxPower = maxPower;
    _lastMaxRPM = maxRPM;
}

const double PowerBench::GetMaxPower() const {
    return _lastMaxPower;
}

const double PowerBench::GetMaxRPM() const {
    return _lastMaxRPM;
}
