#include "sensordata.h"
#include <iostream>
using namespace std;
struct Node {
	SensorData *data;
	Node *next_by_sector;
	Node *next_by_iron;
	Node*next_by_silicon;
	Node(){
		data = new SensorData(0,0,0);
		next_by_sector = nullptr;
		next_by_iron = nullptr;
		next_by_silicon = nullptr;
	}
	~Node(){
		if(data){
			delete data;
		}
		data = nullptr;
	}

};
class LinkedList{
	private:
		Node *head_by_sector;
		Node *head_by_iron;
		Node *head_by_silicon;
		int count;
	public:
		LinkedList(); // defualt constructor
		LinkedList(const LinkedList &copyList); // copy construcotr
		~LinkedList(); //destructor
		LinkedList& operator=(const LinkedList& aList); //assignment op overload
		// methods
		void addSensorData(SensorData& sensor); // insert sensor to list, preserving sorts orders
		void printListBySector();
		void printListByIron();
		void printListBySilicon();
		void printListByAvgs();	
		void printSectorAvgs(int sectorNum);	
		int maxSectorNum();
		bool containsSector(int sectorNum);
		void removeSector(int sectorNum);
		void printSectorsInList();
};
