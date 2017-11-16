#include"Model.h"
#include<sstream>
#include<iostream>

void Model::read(string& filename)
{
	ifstream ifs;
	ifs.open(filename);
	if (ifs.fail())
	{
		throw ios_base::failure("could not open " + filename);
	}
	string line = "";
	string objectData = "";
	int numOfAttributes = 0;
	while (true)
	{
		getline(ifs, line);
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


void Model::print(ofstream& ofs)
{
	for (vector<DataObject>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		ofs << (*it) << endl;
	}
}

size_t Model::getSize()
{
	return objects.size();
}


ofstream& operator<<(ofstream& ofs, Model& model)
{
	for (auto& elem : model.objects)
	{
		ofs << elem;
	}
	ofs << endl;
	return ofs;
}