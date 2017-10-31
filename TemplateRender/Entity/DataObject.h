#include<map>
#include<vector>
#include<string>
using namespace std;

class DataObject
{
private:
	map<string, string> attributes;
	size_t numOfAttributes;
public:
	DataObject();
	DataObject(size_t n);
	DataObject(size_t n, map<string, string>);
	string getInfo();
	map<string, string> getEnumerator();
	size_t getSize();
	friend istream& operator>>(istream& is, DataObject& ob);
	friend ostream& operator<<(ostream& os, DataObject& ob);
	string operator[](string key);
	string operator[](size_t index);
};