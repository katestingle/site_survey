class SensorData{
	private:
		// each sectior contains 3 data vlaues:
		int sectorNum, ironLev, siliconLev;
	public:
		// single constructor accepting all 3 data vals
		SensorData(int sectorNum, int ironLev, int siliconLev);
		// getters
		int getSectorNum();
		int getIronLev();
		int getSiliconLev();
		//FREE to add additional method as see fit, except for additional constructors
		SensorData& operator=(SensorData &aSensor); 
};
