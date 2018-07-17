//	SortingProject.cpp
//	Joshua Castelli

#include "getFile.h"
#include "stdafx.h"


getFile::getFile() {};

string* getFile::loadFromFile(string fileName, int size) {
	ifstream fin;
	fin.open(fileName);
	fileSize = size;

	itemHolder = new string[fileSize];

	if (didConnectToFile(fin, fileName)) {
		for (int i = 0; i < fileSize; i++) {
			getline(fin, itemHolder[i]);
		}
		fin.close();
	}
	else {
		throw logic_error("Error: File did not open");
	}
	return itemHolder;
}

bool getFile::didConnectToFile(ifstream& fin, const string& filename) {
	return fin.is_open();
};

void getFile::toString() {
	for (int i = 0; i <= fileSize; i++) {
		cout << itemHolder[i] << endl;
	}
};