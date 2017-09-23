#include"DataManager.h"
#include<sstream>
#include<iostream>

void DataManager::readObjects(string& filename)
{
	ifstream fin;
	fin.open(filename);
	string line = "";
	map<string, string>* attributes;
	string objectData = "";
	int numOfAttributes = 0;
	while (true)
	{
		getline(fin, line);
		if (line == ".") break;
		else if (line == "#")
		{
			if (objectData.size() != 0)
			{
				stringstream ss(objectData);
				DataObject object(numOfAttributes);
				ss >> object;
				objects.push_back(object);
			}
			numOfAttributes = 0;
			objectData = "";
		}
		else
		{
			objectData += line;
			objectData += " ";
			numOfAttributes++;
		}
	}
}

DataManager::DataManager(string filename)
{
	readObjects(filename);
}

void DataManager::print()
{
	for (vector<DataObject>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		cout << (*it) << endl;
	}
}

vector<DataObject> DataManager::getObjects()
{
	return objects;
}