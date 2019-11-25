#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <iostream>
#include "BPM.h"
#include <map>
#include <vector>
#include <numeric>
#include "boost/algorithm/string/split.hpp"
#include <boost/make_shared.hpp>
#include <boost/circular_buffer.hpp>

BPM::BPM()
{}

BPM::BPM(const std::map<std::string, std::string> &paramsMap, bool isVirtual) :
Hardware(paramsMap, isVirtual),
bpmType(paramsMap.find("bpm_type")->second)
{
	bufferSize = 10;
	name = paramsMap.find("name")->second;
	epicsInterface = boost::make_shared<EPICSBPMInterface>(EPICSBPMInterface());
	xBuffer.resize(bufferSize);
	xPVBuffer.resize(bufferSize);
	yBuffer.resize(bufferSize);
	yPVBuffer.resize(bufferSize);
	qBuffer.resize(bufferSize);
	dataBuffer.resize(bufferSize);
	for(auto && it: dataBuffer)
		{
			it.resize(9);
		}
	pu1Buffer.resize(bufferSize);
	pu2Buffer.resize(bufferSize);
	pu3Buffer.resize(bufferSize);
	pu4Buffer.resize(bufferSize);
	c1Buffer.resize(bufferSize);
	c2Buffer.resize(bufferSize);
	p1Buffer.resize(bufferSize);
	p2Buffer.resize(bufferSize);
	att1Cal = std::stol(paramsMap.find("att1cal")->second);
	att2Cal = std::stol(paramsMap.find("att2cal")->second);
	v1Cal = std::stod(paramsMap.find("v1cal")->second);
	v2Cal = std::stod(paramsMap.find("v2cal")->second);
	qCal = std::stod(paramsMap.find("qcal")->second);
	mn = std::stod(paramsMap.find("mn")->second);
	position = std::stod(paramsMap.find("position")->second);
}
BPM::BPM(const BPM& copyBPM) : 
Hardware(copyBPM),
bpmType(copyBPM.bpmType),
epicsInterface(copyBPM.epicsInterface)
{
}
std::vector<std::string> BPM::getAliases() const
{
	return this->aliases;
}

std::string BPM::getBPMType() const
{
	return this->bpmType;
}

//STATE BPM::getBPMState() const
//{
//	return bpmState;
//}

double BPM::getX() const
{
	return this->x;
}

double BPM::getXFromPV() const
{
	return this->xPV;
}

double BPM::getY() const
{
	return this->y;
}

double BPM::getYFromPV() const
{
	return this->yPV;
}

double BPM::getQ() const
{
	return this->q;
}

double BPM::getResolution() const
{
	return this->resolution;
}

double BPM::getPosition() const
{
	return this->position;
}

size_t BPM::getBufferSize() const
{
	return this->bufferSize;
}

boost::circular_buffer< double > BPM::getBPMXBuffer() const
{
	return this->xBuffer;
}

boost::circular_buffer< double > BPM::getBPMXPVBuffer() const
{
	return this->xPVBuffer;
}

boost::circular_buffer< double > BPM::getBPMYBuffer() const
{
	return this->yBuffer;
}

boost::circular_buffer< double > BPM::getBPMYPVBuffer() const
{
	return this->yPVBuffer;
}

boost::circular_buffer< double > BPM::getBPMQBuffer() const
{
	return this->qBuffer;
}

boost::circular_buffer< std::vector< double > > BPM::getBPMRawDataBuffer() const
{
	return this->dataBuffer;
}

long BPM::getSA1() const
{
	return this->sa1;
}

long BPM::getSA2() const
{
	return this->sa2;
}

long BPM::getSD1() const
{
	return this->sd1;
}

long BPM::getSD2() const
{
	return this->sd2;
}

long BPM::getRA1() const
{
	return this->ra1;
}

long BPM::getRA2() const
{
	return this->ra2;
}

long BPM::getRD1() const
{
	return this->rd1;
}

long BPM::getRD2() const
{
	return this->rd2;
}

bool BPM::setXPV(const double& value)
{
	xPV = value;
	xPVBuffer.push_back(value);
	return true;
}

bool BPM::setYPV(const double& value)
{
	yPV = value;
	xPVBuffer.push_back(value);
	return true;
}

bool BPM::setRA1(const long& value)
{
	ra1 = value;
	return true;
}

bool BPM::setRA2(const long& value)
{
	ra2 = value;
	return true;
}

bool BPM::setRD1(const long& value)
{
	rd1 = value;
	return true;
}

bool BPM::setRD2(const long& value)
{
	rd2 = value;
	return true;
}

bool BPM::setSA1(const long& value)
{
	sa1 = value;
	return true;
}

bool BPM::setSA2(const long& value)
{
	sa2 = value;
	return true;
}

bool BPM::setSD1(const long& value)
{
	sd1 = value;
	return true;
}

bool BPM::setSD2(const long& value)
{
	sd2 = value;
	return true;
}

bool BPM::setAWAK(const long& value)
{
	awak = value;
	return true;
}

bool BPM::setAWAKTStamp(const double& value)
{
	awaktstamp = value;
	return true;
}

bool BPM::setRDY(const long& value)
{
	rdy = value;
	return true;
}

bool BPM::setRDYTStamp(const double& value)
{
	rdytstamp = value;
	return true;
}

bool BPM::setData(const std::vector< double >& value)
{
	data = value;
	pu1 = value[1];
	pu2 = value[2];
	c1 = value[3];
	p1 = value[4];
	pu3 = value[5];
	pu4 = value[6];
	c2 = value[7];
	p2 = value[8];
	dataBuffer.push_back(value);
	pu1Buffer.push_back(pu1);
	pu2Buffer.push_back(pu2);
	pu3Buffer.push_back(pu3);
	pu4Buffer.push_back(pu4);
	c1Buffer.push_back(c1);
	c2Buffer.push_back(c2);
	p1Buffer.push_back(p1);
	p2Buffer.push_back(p2);
	setResolution();
	return true;
}

bool BPM::setQ(const std::vector< double >& rawData)
{
	double q;

	double v1, v2, q1, q2;
	double u11, u12, u13, u14, u21, u22, u23, u24;
	long ra1, ra2;
	u11 = rawData[1];
	u12 = rawData[2];
	u13 = rawData[3];
	u14 = rawData[4];
	u21 = rawData[5];
	u22 = rawData[6];
	u23 = rawData[7];
	u24 = rawData[8];

	v1 = (std::abs(u11 - u14) + std::abs(u12 - u14)) / 2;
	v2 = (std::abs(u21 - u24) + std::abs(u22 - u24)) / 2;
	q1 = (qCal * (v1 / v1Cal)) * (pow(10, -((att1Cal - ra1) / 20)));
	q2 = (qCal * (v2 / v2Cal)) * (pow(10, -((att2Cal - ra2) / 20)));
	q = ((q1 + q2) / 2);

	return true;
}

bool BPM::setResolution()
{
	double u11, u12, u13, u14, u21, u22, u23, u24, v11, v12, v21, v22;
	double rmsVals;
	u11 = std::accumulate(pu1Buffer.begin(), pu1Buffer.end(), 0.0) / pu1Buffer.size();
	u12 = std::accumulate(pu2Buffer.begin(), pu2Buffer.end(), 0.0) / pu2Buffer.size();
	u13 = std::accumulate(c1Buffer.begin(), c1Buffer.end(), 0.0) / c1Buffer.size();
	u14 = std::accumulate(p1Buffer.begin(), p1Buffer.end(), 0.0) / p1Buffer.size();
	u21 = std::accumulate(pu3Buffer.begin(), pu3Buffer.end(), 0.0) / pu3Buffer.size();
	u22 = std::accumulate(pu4Buffer.begin(), pu4Buffer.end(), 0.0) / pu4Buffer.size();
	u23 = std::accumulate(c2Buffer.begin(), c2Buffer.end(), 0.0) / c2Buffer.size();
	u24 = std::accumulate(p2Buffer.begin(), p2Buffer.end(), 0.0) / p2Buffer.size();
	v11 = u11 - u14;
	v12 = u12 - u14;
	v21 = u21 - u24;
	v22 = u22 - u24;
	if (v11 && v12 && v21 && v22 != 0)
	{
		rmsVals = ((v11 + v12) - (v21 + v22)) / ((v11 + v12) + (v21 + v22));
	}
	resolution = rmsVals * sqrt(2) * (0.001 * mn);
	return true;
}

bool BPM::checkBuffer(boost::circular_buffer< double >& buf)
{
	if (buf[buf.size() - 1] == buf[buf.size()])
	{
		return true;
	}
	return false;
}

//void BPM::checkStatus()
//{
//	if (awaktstamp - rdytstamp > 1.0)
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::BAD;
//		statusBuffer.push_back(status);
//	}
//	else if (checkBuffer(xBuffer) || checkBuffer(yBuffer))
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::BAD;
//		statusBuffer.push_back(status);
//	}
//	else if (checkBuffer(pu1Buffer) || checkBuffer(pu2Buffer) || checkBuffer(pu3Buffer) || checkBuffer(pu4Buffer))
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::BAD;
//		statusBuffer.push_back(status);
//	}
//	else if (isnan(xBuffer.back()) || isnan(yBuffer.back()))
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::BAD;
//		statusBuffer.push_back(bpmdo->status);
//	}
//	else if (abs(pu1Buffer.back()) > 1.0 || abs(pu2Buffer.back()) > 1.0 || abs(pu3Buffer.back()) > 1.0 || abs(pu4Buffer.back()) > 1.0)
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::NONLINEAR;
//		statusBuffer.push_back(status);
//	}
//	else if (abs(pu1Buffer.back()) < 1.0 || abs(pu2Buffer.back()) < 1.0 || abs(pu3Buffer.back()) < 1.0 || abs(pu4Buffer.back()) < 1.0)
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::GOOD;
//		statusBuffer.push_back(status);
//	}
//	else
//	{
//		status = beamPositionMonitorStructs::BPM_STATUS::UNKNOWN;
//		statusBuffer.push_back(status);
//	}
//}

bool BPM::reCalAttenuation(const double& charge)
{
	double qqC = charge / qCal;

	long currAtt1 = ra1;
	long currAtt2 = ra2;

	long newAtt1 = (20 * log10(qqC)) + att1Cal;
	long newAtt2 = (20 * log10(qqC)) + att2Cal;

	if (0 <= newAtt1 && newAtt1 <= 20)
	{
		setSA1(newAtt1);
	}
	else if (charge < 20)
	{
		setSA1(0);
	}
	else
	{
		setSA1(currAtt1);
	}


	if (0 <= newAtt2 && newAtt2 <= 20)
	{
		setSA2(newAtt2);
	}
	else if (charge < 20)
	{
		setSA2(0);
		//message("New SA2 for ", name, " = ", getRA2());
	}
	else
	{
		setSA2(currAtt2);
		//message("Old SA2 for ", name, " = ", getRA2());
	}
	return true;
}

void BPM::setBufferSize(const size_t& value)
{
	bufferSize = value;
	xBuffer.resize(bufferSize);
	xPVBuffer.resize(bufferSize);
	yBuffer.resize(bufferSize);
	yPVBuffer.resize(bufferSize);
	qBuffer.resize(bufferSize);
	dataBuffer.resize(bufferSize);
	pu1Buffer.resize(bufferSize);
	pu2Buffer.resize(bufferSize);
	pu3Buffer.resize(bufferSize);
	pu4Buffer.resize(bufferSize);
	c1Buffer.resize(bufferSize);
	c2Buffer.resize(bufferSize);
	p1Buffer.resize(bufferSize);
	p2Buffer.resize(bufferSize);
	for (auto&& it2 : dataBuffer)
	{
		it2.resize(9);
	}
}

void BPM::clearBuffers()
{
	xBuffer.clear();
	xPVBuffer.clear();
	yBuffer.clear();
	yPVBuffer.clear();
	qBuffer.clear();
	dataBuffer.clear();
	pu1Buffer.clear();
	pu2Buffer.clear();
	pu3Buffer.clear();
	pu4Buffer.clear();
	c1Buffer.clear();
	c2Buffer.clear();
	p1Buffer.clear();
	p2Buffer.clear();
}