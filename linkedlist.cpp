#include "linkedlist.h"
//Default constructor
LinkedList::LinkedList(){
	head_by_sector = nullptr;
	head_by_iron = nullptr;
	head_by_silicon = nullptr;
	count = 0;
}
//copy constructor
LinkedList::LinkedList(LinkedList const &copyList){
	*this = copyList;
}
//destructor
LinkedList::~LinkedList(){
	if(head_by_sector != nullptr){
		Node  *curr = head_by_sector;
		while(curr) {
			Node *temp = curr->next_by_sector;
			delete curr;
			curr = temp;;
		}
	}
	head_by_sector = nullptr;
}
// assignment operator overload
LinkedList& LinkedList::operator=(const LinkedList &aList){
	if(this == &aList){
		//self-assignment
		return *this;
	}
	//keep going to assign
	return *this;
}
// adding SensorData object to list
void LinkedList::addSensorData(SensorData &sensor){
	Node *newNode = new Node(); // creat new node
	*(newNode->data) = sensor;
       newNode->next_by_iron = nullptr;
	newNode->next_by_silicon = nullptr;       
	newNode->next_by_sector = nullptr; // by default
	// then inset by sector number
	int newSectorNum = (newNode->data)->getSectorNum();
	int newIronLev = (newNode->data)->getIronLev();
	int newSiliconLev = (newNode->data)->getSiliconLev();
	if(!head_by_sector){ // no items in list
		head_by_sector = newNode;
		head_by_iron = newNode;
		head_by_silicon = newNode;
	} else{
		// at least 1 item in list
		Node *curr = head_by_sector; // start at beginning of traversal
		Node *prev = nullptr;
		// SECTOR NUM LIST
		if(newSectorNum <= (curr->data)->getSectorNum()){
			// insert @head
			newNode->next_by_sector  = head_by_sector;
			head_by_sector = newNode;
		} else { // insertin body/end
			while(curr && (newSectorNum > (curr->data)->getSectorNum())){
				prev = curr;
				curr = curr->next_by_sector;
			}
			// newNode should now be placed at prev
			prev->next_by_sector = newNode;
			newNode->next_by_sector = curr;
		}
		// IRON LIST
		curr = head_by_iron;
		prev = nullptr;
		if(newIronLev <= (curr->data)->getIronLev()){
			//insert @head
			newNode->next_by_iron = head_by_iron;
			head_by_iron = newNode;
		} else { // insert in body/end
			while(curr && (newIronLev > (curr->data)->getIronLev())){
				prev = curr;
				curr = curr ->next_by_iron;
			}
			//newNode should now be palce at prev
			prev->next_by_iron = newNode;
			newNode->next_by_iron = curr;
		}
		// SILICON LIST
		curr = head_by_silicon;
		prev = nullptr;
		if(newSiliconLev <= (curr->data)->getSiliconLev()){
			// insert @head
			newNode->next_by_silicon = head_by_silicon;
			head_by_silicon = newNode;
		} else {  //insert in body/end
			while(curr && (newSiliconLev > (curr->data)->getSiliconLev())){
				prev = curr;
				curr = curr->next_by_silicon;
			}
			// newNode should now be placed at prev
			prev->next_by_silicon = newNode;
			newNode->next_by_silicon = curr;
		}
		curr = nullptr;
		prev = nullptr;
	}

}
// print the olist by each sector
void LinkedList::printListBySector(){
	Node *curr = head_by_sector;
	while(curr){
		cout << "Sector: #" << (curr->data)->getSectorNum() << " " ;
	        cout << (curr->data)->getIronLev() << " grams iron, ";
	        cout << (curr->data)->getSiliconLev() << " milligrams silicon" << endl;
		curr = curr->next_by_sector;
	}
}
//print the list by iron in ascending order
void LinkedList::printListByIron(){
	Node *curr = head_by_iron;
	while(curr){
		cout << "Sector: #" << (curr->data)->getSectorNum() << " ";
		cout << (curr->data)->getIronLev() << " grams iron, ";
		cout << (curr->data)->getSiliconLev() << " milligrams silicon" << endl;
		curr = curr -> next_by_iron;
	}
}
// print the list by silicon in ascending order
void LinkedList::printListBySilicon(){
	Node *curr = head_by_silicon;
	while(curr){
		cout << "Sector: #" << (curr->data)->getSectorNum() << " ";
		cout << (curr->data)->getIronLev() << " grams iron, ";
		cout << (curr->data)->getSiliconLev() << " milligrams silicon" << endl;
		curr = curr -> next_by_silicon;
	}
}

void LinkedList::printListByAvgs(){
	for(int i = 1; i <= maxSectorNum(); i++){
		printSectorAvgs(i);
	}	
}

int LinkedList::maxSectorNum(){ // returns the maximum sector number of the whole list
	Node*curr = head_by_sector;
	int max = 0;
	while(curr){
		if(curr->data->getSectorNum() > max){
			max = curr->data->getSectorNum();
		}
		curr = curr->next_by_sector;	
	}
	return max;
}

void LinkedList::printSectorAvgs(int sectorNum){
	Node*curr = head_by_sector;
	int avgIron = 0, avgSilicon = 0;
	int countValidEntries = 0;
	while(curr){
		if((curr->data)->getSectorNum() == sectorNum){ // add to avg
			if(curr->data->getIronLev() >0 && curr->data->getSiliconLev() > 0){ // only consider if iron and silicon lev are valid
				countValidEntries++;
				avgIron  += curr->data->getIronLev();
				avgSilicon += curr->data->getSiliconLev();
			}
		}
		curr = curr->next_by_sector;	
	}	// summation complete
	// search for Sectors is complete
	cout << "Sector: #" << sectorNum << " ";
	if(countValidEntries == 0){ // if no valid data for hte current sector 
       		cout << " -- no data -- "<<endl;
	} else {
		avgIron /= countValidEntries;
		avgSilicon /= countValidEntries;	
		cout << avgIron << " grams iron, ";
		cout << avgSilicon << " milligrams silicon" << endl;
	}
}
bool LinkedList::containsSector(int sectorNum){
	Node*curr = head_by_sector;
	while(curr){
		if(curr->data->getSectorNum() == sectorNum){
			return true;
		}
		curr=curr->next_by_sector;
	}
	return false;
}
void LinkedList::removeSector(int sectorNum){
	// whne we deallocate, the memory is droppede from the heap
	// meaning that that other lists will lose it ad well
	Node *sectorToRemove = nullptr;
	while(containsSector(sectorNum)){ // repeat the singular sensordata obj removal until all of them are gone from same sector
		// remove sector
		Node *curr = head_by_sector;
		Node *prev = nullptr;
		while(curr->data->getSectorNum() != sectorNum){ //traverse until find sector
			prev = curr;
			curr = curr->next_by_sector;
		} 
		//now, curr points to the SensorData Obj we want to remove
		sectorToRemove = curr; // this "saves" the sector to remove while we edit each list before deallocating
		// EDIT SETOR LIST
		if(sectorToRemove == head_by_sector) {//head remove
			head_by_sector = head_by_sector -> next_by_sector;
		} else { //remove in body/end
			prev ->next_by_sector = curr->next_by_sector;
		}
		// EDIT IRON LIST
		curr = head_by_iron;
		prev = nullptr; // reset before traversing to find remove secot'rs locaiton in _by_iron list
		while(curr != sectorToRemove){
			prev = curr;
			curr = curr->next_by_iron;
		} // keep going until found the locaiton where the remove sector is in the list
		if(sectorToRemove == head_by_iron) { //remove at head
			head_by_iron = head_by_iron -> next_by_iron;
		} else { //remove in body/end
			prev ->next_by_iron = curr-> next_by_iron;
		}
		// EDITE SILICON LIST
		curr = head_by_silicon;
		prev = nullptr;
		while(curr != sectorToRemove){
			prev = curr;
			curr = curr->next_by_silicon;
		} // keep goin until found where remove sector is in _by_silicon list
		if(sectorToRemove == head_by_silicon) { //remove at head of silicon list
			head_by_silicon = head_by_silicon ->next_by_silicon;
		} else { //remove in body/end
			prev -> next_by_silicon = curr ->next_by_silicon;
		}
		// DONE EDITING LIST POINTERS, so we can deallocate the memory for the sector that we "saved" that we will remove
		delete sectorToRemove;
		sectorToRemove = nullptr;
		curr = nullptr;
		prev = nullptr;
	}
}
void LinkedList::printSectorsInList(){
	Node*curr = head_by_sector;
	while(curr){
		if(curr != head_by_sector) {
			cout << ", ";
		}
		cout << curr->data->getSectorNum() ;
		curr = curr->next_by_sector;
	}
	cout << endl;
	curr = nullptr;
}
