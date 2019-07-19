#ifndef HARDWARE_FACTORY_H_
#define HARDWARE_FACTORY_H_
#include "MagnetFactory.h"

class HardwareFactory
{
    //what does a HardwareFactory need to be a HardwareFactory:
    /*
    *   - A Hardware HardwareFactory Type (ENUM/DEFINES?)
    *   - A Hardware HardwareFactory Name (string/ENUM?)
    *   - Needs to invoke LoggingSystem object without having it as an inherited member.
    *
    */
public:
	HardwareFactory();
	HardwareFactory(bool isVirtual);
	HardwareFactory(std::string hardwareType, std::string version);
	bool setup(std::string hardwareType, std::string version);
	MagnetFactory getMagnetFactory();
	Magnet* getMagnet(std::string fullMagnetName);
	std::vector<Magnet*> getAllMagnets();
	bool operator ==(const HardwareFactory &HardwareFactory) const;
	LoggingSystem messenger;
	ConfigReader reader;
	//std::vector<Hardware*> hardwareVector;
	std::vector<Hardware*> hardwareVector;
	MagnetFactory magnetFactory;
	bool isVirtual;
};


#endif // HardwareFactory_H_