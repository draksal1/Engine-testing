#include "Engine.h"



PiecewiseLinearFunction::PiecewiseLinearFunction(const std::vector<double>& V, const std::vector<double>& M) {
	if (V.size() != M.size()) {
		throw std::invalid_argument("V and M vectors must be of the same length");
	}

	for (size_t i = 0; i < V.size(); ++i) {
		_points.push_back(std::make_pair(V[i], M[i]));
	}
}

double PiecewiseLinearFunction::getTorque(double V) const {
	if (_points.empty()) return 0.0;

	// The simplest linear interpolation
	for (size_t i = 0; i < _points.size() - 1; ++i) {
		if (V >= _points[i].first && V <= _points[i + 1].first) {
			double t = (V - _points[i].first) / (_points[i + 1].first - _points[i].first);
			return _points[i].second + t * (_points[i + 1].second - _points[i].second);
		}
	}

	return _points.back().second;
}



void SimulatedEngine::StartEngine(){
	_isRunning = true;
}

void SimulatedEngine::StopEngine(){
	_isRunning = false;
	this->UpdateState(0.0);
}

bool SimulatedEngine::IsRunning() const {
	return _isRunning;
}

double SimulatedEngine::GetPower() const{
	double M = _torqueCurve.getTorque(_crankshaftSpeed);
	return (M * _crankshaftSpeed) / 1000.0; // Power in kW
}

double SimulatedEngine::GetRPM() const{
	return _crankshaftSpeed;
}

double SimulatedEngine::GetTemperature() const{
	return _engineTemperature;
}

double SimulatedEngine::GetOverheatTemperature() const{
	return _overheatTemperature;
}

void SimulatedEngine::UpdateState(double dt){
	if (_isRunning) {
		double M = _torqueCurve.getTorque(_crankshaftSpeed);
		double a = M / _inertia; // Acceleration

		_crankshaftSpeed += a * dt; // Updating the crankshaft speed
		double VH = M * _hM + _crankshaftSpeed * _crankshaftSpeed * _hV; // Heating rate
		double VC = _c * (_enviromentTemperature - _engineTemperature); // Cooling rate

		_engineTemperature += (VH + VC) * dt; // Updating the engine temperature
	}
	else {
		_crankshaftSpeed = 0; // Updating the crankshaft speed
		_engineTemperature = _enviromentTemperature; // Updating the engine temperaturec
	}
}