#pragma once
#include <fstream>
#include <vector>

// Class which read the configuration files
class ConfigParser
{
public:
	struct Configuration
	{
		double Inertia = 0.0;
		std::vector<double> V = {};
		std::vector<double> M = {};
		double OverheatingTemperature = 0.0;
		double HM = 0.0;
		double HV = 0.0;
		double C = 0.0;
	};

	static const Configuration Parse(std::ifstream& file);
};

