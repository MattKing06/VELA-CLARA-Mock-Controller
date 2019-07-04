#ifndef HARDWARE_H_
#define HARDWARE_H_
#include <map>
#include <vector>
#include <iostream>
#include "LoggingSystem.h"
#include "ConfigReader.h"
#ifndef PV_H_
#include "PV.h"
#endif
class Hardware
{
public:
	// vector of PV structs 
	// string hardware type
	// vector of strings for aliases relating to enums
	Hardware();
	Hardware(std::map<std::string, std::string> paramMap);
	std::string getMachineArea();
	std::string getHardwareType();
	std::vector<pvStruct>* getPVStructs();
	std::map<std::string, std::string> getSpecificHardwareParameters();
	bool operator==(Hardware rhs);
//protected:
	LoggingSystem *logger;
	std::string machineArea;
	std::string hardwareType;
	std::vector<pvStruct> pvStructs;
	std::map<std::string, std::string> specificHardwareParameters;
};
#endif //HARDWARE_H_