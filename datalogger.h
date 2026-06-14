#include "linkedlist.h"
class DataLogger {
	private:
		LinkedList list;
	public:
		// REQUIRED METHODS - COME BACK
		void addData(int sector, int iron, int silicon); // receives data vlaues, bundle into a SensorData obj, then adds to datalog
		bool containsSector(int sector); // checks if a given sector has been added
		void removeSector(int sector); // removes all data associated w the given sector fromt he datalog
		void printReport(); // print data report. 
		void printSectorList(); // prints a lst of all sectors that have been logged
	
};
