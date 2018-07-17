#pragma once

//	SortingProject.cpp
//	Joshua Castelli

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class getFile {
public:
	string * itemHolder;
	int fileSize;

	getFile();
	string* loadFromFile(std::string fileName, int size);

	bool didConnectToFile(ifstream& fin, const string& filename);

	void toString();
};
