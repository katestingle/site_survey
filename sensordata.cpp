#include "sensordata.h"
//CONSTRUCTOR
SensorData::SensorData(int sectorNum, int ironLev, int siliconLev){
	this -> sectorNum = sectorNum;
	this -> ironLev = ironLev;
	this -> siliconLev = siliconLev;
}
// GETTERS
int SensorData::getSectorNum(){
	return sectorNum;
}
int SensorData::getIronLev(){
	return ironLev;
}
int SensorData::getSiliconLev(){
	return siliconLev;
}
SensorData& SensorData::operator=(SensorData &aSensor){
	if(this == &aSensor) { //self assignment
		return *this;
	} else {
		this->sectorNum = aSensor.getSectorNum();
		this->ironLev = aSensor.getIronLev();
		this->siliconLev = aSensor.getSiliconLev();
	}
	return *this;
}
