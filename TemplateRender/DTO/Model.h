#include<vector>
#include<string>
#include<fstream>
#include"../Entity/DataObject.h"
using namespace std;

class Model
{
private:
	typedef vector<DataObject> Objects;
	vector<DataObject> objects;
public:
	typedef Objects::iterator iterator;
	typedef Objects::const_iterator const_iterator;
	iterator begin() { return objects.begin(); }
	iterator end() { return objects.end(); }
	const_iterator cbegin() { return objects.cbegin(); }
	const_iterator cend() { return objects.cend(); }

	void read(string& filename);
	void print(ofstream& ofs);
	size_t getSize();

	friend ofstream& operator<<(ofstream& ofs, Model& model);

};