#include "datalogger.h"
//Creates SensorData bundle object in heap and adds its value to the list
void DataLogger::addData(int sector, int iron, int silicon){
	// uses LinkedList's addSensorData()
	// construct SensorDat9a
	if(sector >0){ // has to do with extraneous sensor data - no sensor should com ein with a negative sectorNum,
		// but int the case of extra.txt that is posssible, so we are testing for extraneous data input like this.
		// negative numbers for the actua irona nd silicon levels is alread dealth with by the program
		// /hence the "bad sectors" section
		// if a sectorNum comes in negative, it is a non-existant secotr, so we discard all info from that sector
	SensorData *newData = new SensorData(sector, iron, silicon); // allocate memory, remember to deallocate
	list.addSensorData(*newData); // adds copy of SensorData to list	
	delete newData; // deallocate newData as the data was already copied in addSensorData
	newData = nullptr;
	}
}

bool DataLogger::containsSector(int sector){
	// RETURN TRUE BY DEFAULT(FOR NOW)
	return list.containsSector(sector);
}

void DataLogger::removeSector(int sector){
	if(list.containsSector(sector)){
		list.removeSector(sector);
	}
}
void DataLogger::printReport(){	
	cout << "----------------------------------------------------------------------" << endl;
    	cout << "Data values" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "List by Sector: " << endl;
	list.printListBySector();
	cout << "List by Iron: " << endl;
	list.printListByIron();
	cout << "List by Silicon:" << endl;
	list.printListBySilicon();
    	cout << "----------------------------------------------------------------------" << endl;
    	cout << "Averages per sector"<<endl;
	cout << "----------------------------------------------------------------------" << endl;
	list.printListByAvgs();
}
void DataLogger::printSectorList(){
	list.printSectorsInList();	
}
