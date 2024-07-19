#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

const ConfigParser::Configuration ConfigParser::Parse(std::ifstream& file) {
    ConfigParser::Configuration config;
    std::string line;

    // Reading Inertia
    if (std::getline(file, line)) {
        config.Inertia = std::stod(line);
    }
    else {
        throw std::invalid_argument("Error reading Inertia");
    }

    // Reading M
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ',')) {
            config.M.push_back(std::stod(value));
        }
    }
    else {
        throw std::invalid_argument("Error reading M");
    }

    // Reading V
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ',')) {
            config.V.push_back(std::stod(value));
        }
    }
    else {
        throw std::invalid_argument("Error reading V");
    }

    // Reading OverheatingTemperature
    if (std::getline(file, line)) {
        config.OverheatingTemperature = std::stod(line);
    }
    else {
        throw std::invalid_argument("Error reading OverheatingTemperature");
    }

    // Reading HM
    if (std::getline(file, line)) {
        config.HM = std::stod(line);
    }
    else {
        throw std::invalid_argument("Error reading HM");
    }

    // Reading HV
    if (std::getline(file, line)) {
        config.HV = std::stod(line);
    }
    else {
        throw std::invalid_argument("Error reading HV");
    }

    // Reading C
    if (std::getline(file, line)) {
        config.C = std::stod(line);
    }
    else {
        throw std::invalid_argument("Error reading C");
    }

    return config;
}