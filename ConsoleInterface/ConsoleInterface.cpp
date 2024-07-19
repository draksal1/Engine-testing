#include <iostream>
#include <string>
#include <fstream>
#include "..//Engine Simulation/Engine.h"
#include "..//Test benches/PowerBench.h"
#include "..//Test benches/TemperatureBench.h"
#include "ConfigParser.h"

void ClearScreen() {
    system("cls");
}

int main()
{
    std::string filename;
    std::ifstream file;
    SimulatedEngine engine = SimulatedEngine();
    double timeStep = 1;

    while (true) {
        std::cout << "This programm tests the engine for time to overheating and maximum power." << std::endl;;
        std::cout << "Please enter the name of configuration file like this: \"EngineConfig.txt\"" << std::endl;
        std::cout << "Enter \"Exit\" to close program" << std::endl;

        std::cin >> filename;

        if (filename == "Exit") {
            return 0;   
        }

        file.open(filename);

        if (!file) {
            ClearScreen();
            std::cerr << "Failed to open/find the file: " << filename << ". Please try again." << std::endl << std::endl;
            file.clear();
            continue;
        }
        
        try {
            ConfigParser::Configuration config = ConfigParser::Parse(file);
            double EnviromentTemperature;
            ClearScreen();
            std::cout << "The file has been successfully read. Enter the enviroment temperature" << std::endl;
            std::cin >> EnviromentTemperature;

            engine = SimulatedEngine(config.Inertia, PiecewiseLinearFunction(config.V, config.M),
                config.OverheatingTemperature, config.HM, config.HV, config.C, EnviromentTemperature);

            break;
        }
        catch (std::invalid_argument) {
            std::cerr << "Bad config file, reboot the program" << std::endl;
            return 0;
        }
    }
    while (true) {
        std::cout << "Choose type of test:\n1.Temperature test.\n2.PowerTest" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        if (input == "Exit") {
            ClearScreen();
            return 0;
        }

        if (input == "1") {
            ClearScreen();
            std::cout << "Selected test: Temperature test." << std::endl;
            TemperatureBench timeBench = TemperatureBench(timeStep);
            try {
                timeBench.TestEngine(engine);
            }
            catch (std::runtime_error exc) {
                ClearScreen();
                std::cout << exc.what() << std::endl << std::endl;
                continue;
            }
            std::cout << "Time to overheating: " << timeBench.GetOverheatingTime() << std::endl;
        }
        else if (input == "2") {
            ClearScreen();
            std::cout << "Selected test: Power test." << std::endl;
            PowerBench powerBench = PowerBench(timeStep);
            powerBench.TestEngine(engine);
            std::cout << "Max power: " << powerBench.GetMaxPower() << "\nWith RPM: " << powerBench.GetMaxRPM() << std::endl;
        }
        else {
            std::cout << "Invalid input. Please enter 1, 2 or 'Exit'." << std::endl;
            continue;
        }
    }
    return 0;
}
