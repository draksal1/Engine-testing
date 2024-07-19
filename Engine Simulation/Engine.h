#pragma once
#include <vector>
#include <stdexcept>

// Abstract class, added for scalability
class Engine
{
public:
	virtual void StartEngine() = 0;
	virtual void StopEngine() = 0;
	virtual void UpdateState(double dt) = 0;
	virtual double GetRPM() const = 0;
	virtual double GetPower() const = 0;
	virtual double GetTemperature() const = 0;
	virtual double GetOverheatTemperature() const = 0;
};



// Class for representing piecewise linear dependence
class PiecewiseLinearFunction {
private:
	std::vector<std::pair<double, double>> _points;

public:
	PiecewiseLinearFunction() = default;

	PiecewiseLinearFunction(const std::vector<double>& V, const std::vector<double>& M);

	double getTorque(double V) const;
};

// Class for engine simulation
class SimulatedEngine : public Engine {
private:
	double _inertia = 0.0;
	PiecewiseLinearFunction _torqueCurve;
	double _overheatTemperature = 0.0;
	double _hM = 0.0; // Coefficient of dependence of heating rate on torque
	double _hV = 0.0; // Coefficient of dependence of heating rate on crankshaft speed
	double _c = 0.0; // Coefficient of dependence of cooling ratec
	double _enviromentTemperature = 0.0;

	double _crankshaftSpeed = 0.0;
	double _engineTemperature = 0.0;
	bool _isRunning = false;

public:
	SimulatedEngine(double I, const PiecewiseLinearFunction& torqueCurve, double T_overheat,
		double HM, double HV, double C, double T_environment)
		: _inertia(I), _torqueCurve(torqueCurve), _overheatTemperature(T_overheat),
		_hM(HM), _hV(HV), _c(C), _enviromentTemperature(T_environment), _crankshaftSpeed(0.0),
		_engineTemperature(T_environment), _isRunning(false) {}

	SimulatedEngine() = default;
	
	void StartEngine() override;

	void StopEngine() override;

	bool IsRunning() const;

	double GetPower() const override;

	double GetRPM() const override;

	double GetTemperature() const override;

	double GetOverheatTemperature() const override;

	void UpdateState(double dt) override;
};
