#include<map>
#include<vector>
#include<string>
using namespace std;

class DataObject
{
private:
	map<string, string> attributes;
	int numOfAttributes;
public:
	DataObject();
	DataObject(int n);
	DataObject(int n, map<string, string>);
	friend istream& operator>>(istream& is, DataObject& ob);
	friend ostream& operator<<(ostream& os, DataObject& ob);
	string operator[](string key);
};