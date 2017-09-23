#include<vector>
#include<string>
#include<fstream>
#include"DataObject.h"
using namespace std;

class DataManager
{
private:
	vector<DataObject> objects;
	void readObjects(string& filename);
public:
	DataManager(string filename);
	void print();
	vector<DataObject> getObjects();
};