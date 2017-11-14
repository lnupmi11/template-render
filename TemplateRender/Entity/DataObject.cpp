#include"DataObject.h"

DataObject::DataObject()
{
	numOfAttributes = 0;
}

DataObject::DataObject(int _numOfAttributes)
{
	numOfAttributes = _numOfAttributes;
}

DataObject::DataObject(int _numOfAttributes, map<string, string> _attributes)
{
	numOfAttributes = _numOfAttributes;
	attributes = _attributes;
}

string DataObject::getInfo()
{
	return string();
}

map<string, string> DataObject::getEnumerator()
{
	return this->attributes;
}

size_t DataObject::getSize()
{
	return this->numOfAttributes;
}

istream& operator>>(istream& is, DataObject& obj)
{
	string key, value;
	for (int i = 0; i < obj.numOfAttributes; ++i)
	{
		is >> key >> value;
		obj.attributes[key] = value;
	}
	return is;
}

ostream& operator<<(ostream& os, DataObject& obj)
{
	for (map<string, string>::iterator it = obj.attributes.begin(); it != obj.attributes.end(); ++it)
	{
		os << it->first << " " << it->second << endl;
	}
	return os;
}

string DataObject::operator[](string key)
{
	return attributes[key];
}

