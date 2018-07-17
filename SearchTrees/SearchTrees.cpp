// RedBlackTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "getFile.h"
#include "BST.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <time.h>
using namespace std;

/*Globals*/
float buildTime, queryTime;

/*File size selection*/
int selectFileSize() {
	string selectionStr;
	int selection;
	bool valid = false;

	while (valid == false) {
		while (true) {
			system("CLS");
			cout << "Please select the file size you wish to use\n";
			cout << "1 - 30k words\n";
			cout << "2 - 60k words\n";
			cout << "3 - 90k words\n";
			cout << "4 - 120k words\n";
			cout << "5 - 150k words\n";
			cout << "6 - Exit\n";
			cout << "Selection(1-6): ";

			getline(cin, selectionStr);

			stringstream myStream(selectionStr);
			if (myStream >> selection) {
				break;
			}
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}

		if (selection > 6 && selection < 1) {
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}
		else {
			switch (selection) {
			case 1: selection = 30000;
				break;
			case 2: selection = 60000;
				break;
			case 3: selection = 90000;
				break;
			case 4: selection = 120000;
				break;
			case 5: selection = 150000;
				break;
			case 6: exit(0);
			}
			valid = true;
		}
	}
	return selection;
}
/*Permuted or Sorted selection*/
int selectPermutedOrSorted() {
	string selectionStr;
	int selection;
	bool valid = false;

	while (valid == false) {
		while (true) {
			system("CLS");
			cout << "Please select the sorthing algorithm you wish to use\n";
			cout << "1 - Permuted\n";
			cout << "2 - Sorted\n";
			cout << "3 - Exit\n";
			cout << "Selection(1-3): ";

			getline(cin, selectionStr);

			stringstream myStream(selectionStr);
			if (myStream >> selection) {
				if (selection == 3)
					exit(0);
				break;
			}
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}

		if (selection > 3 && selection < 1) {
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}
		else {
			valid = true;
		}
	}
	return selection;
}
/*Tree structure selection*/
int selectStructure() {
	int treeSelection;
	string tree;
	bool valid = false;
	system("CLS");
	while (!valid) {
		while (true) {
			cout << "Select tree structure" << endl;
			cout << "1 - BST" << endl;
			cout << "2 - Red-Black" << endl;
			cout << "3 - Exit" << endl;
			cout << "Selection:";
			getline(cin, tree);

			stringstream myStream(tree);
			if (myStream >> treeSelection) {
				if (treeSelection == 3)
					exit(0);
				break;
			}
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}
		if (treeSelection > 3 || treeSelection < 1) {
			system("CLS");
			cout << "!!!INCORRECT SELECTION, TRY AGAIN!!! \n";
		}
		else {
			valid = true;
		}
	}
	return treeSelection;
}
/*Open and extract file*/
string* openFile(int permOrSort, int size, string fileName) {
	if (permOrSort == 1) {
		fileName = "permuted/";
	}
	else {
		fileName = "sorted/";
	}

	switch (size) {
	case 30000: fileName += "30K.txt";
		break;
	case 60000: fileName += "60K.txt";
		break;
	case 90000: fileName += "90K.txt";
		break;
	case 120000: fileName += "120K.txt";
		break;
	case 150000: fileName += "150K.txt";
		break;
	}

	system("CLS");
	cout << "Loading file..." << endl;
	string* temp;
	getFile inputFile;
	temp = inputFile.loadFromFile(fileName, size);
	return temp;
};
/*BST output*/
void outputBST(BST::node found, string searchString) {
	////OUTPUT////

	if (found.key == searchString) {
		cout << "'" + searchString + "' was found!" << endl;
		cout << "Build Time: " << buildTime << "ms" << endl;
		cout << "Query Time: " << queryTime << "ms" << endl;
	}
	else {
		cout << "'" + searchString + "' was NOT found" << endl;
		cout << "Build Time: " << buildTime << "ms" << endl;
		cout << "Query Time: " << queryTime << "ms" << endl;
	}

	/* debugging purposes only:
	//
	cout << "Min from " + found.key + ": " + tree->treeMin(&found) << endl;
	cout << "Max from " + found.key + ": " + tree->treeMax(&found) << endl;
	cout << "Successor of " + found.key + ": " + tree->treeSuccessor(&found) << endl;
	cout << "Predecessor of " + found.key + ": " + tree->treePredecessor(&found) << endl;
	tree->inorderTreeWalk(tree->root);
	system("PAUSE");
	*/

	//////////////
}
/*RBT output*/
void outputRBT(RBT::node found, string searchString) {
	////OUTPUT////

	if (found.key == searchString) {
		cout << "'" + searchString + "' was found!" << endl;
		cout << "Build Time: " << buildTime << "ms" << endl;
		cout << "Query Time: " << queryTime << "ms" << endl;
	}
	else {
		cout << "'" + searchString + "' was NOT found" << endl;
		cout << "Build Time: " << buildTime << "ms" << endl;
		cout << "Query Time: " << queryTime << "ms" << endl;
	}

	/* debugging purposes only:
	//
	cout << "Min from " + found.key + ": " + tree->treeMin(&found) << endl;
	cout << "Max from " + found.key + ": " + tree->treeMax(&found) << endl;
	cout << "Successor of " + found.key + ": " + tree->treeSuccessor(&found) << endl;
	cout << "Predecessor of " + found.key + ": " + tree->treePredecessor(&found) << endl;
	tree->inorderTreeWalk(tree->root);
	system("PAUSE");
	*/

	//////////////
}
/*Build tree structure and search for user input within*/
void buildAndSearch(int treeSelection,string*temp,int size,string searchString) {
	clock_t bT;
	clock_t qT;

//BST selected//
	if (treeSelection == 1) {

		BST*tree;
		tree = new BST;
		BST::node found;

		//Build Tree
		bT = clock();
		tree->buildTree(tree, temp, size);
		buildTime = ((float)(clock() - bT) / CLOCKS_PER_SEC) * 1000;

		//Search Tree
		qT = clock();
		found = tree->iterativeTreeSearch(tree->root, searchString);
		queryTime = ((float)(clock() - qT) / CLOCKS_PER_SEC) * 1000;

		outputBST(found, searchString);

	}
//RBT Selected//
	else {

		RBT *tree;
		tree = new RBT;
		RBT::node found;

		//Build Tree
		bT = clock();
		tree->buildTree(tree, temp, size);
		buildTime = ((float)(clock() - bT) / CLOCKS_PER_SEC) * 1000;

		//Search Tree
		qT = clock();
		found = tree->iterativeTreeSearch(tree->root, searchString);
		queryTime = ((float)(clock() - qT) / CLOCKS_PER_SEC) * 1000;

		outputRBT(found, searchString);

	}
};


/* MAIN */
int main()
{
begin:
	buildTime = 0;
	queryTime = 0;
	system("CLS");
	//Variables
	string searchString, *temp;
	int treeSelection, size, permOrSort;
	string fileName;

	//Begin Console UI
	cout << "Please type the word you wish to search for." << endl;
	cout << "Search: ";
	getline(cin, searchString);
	
	//Converts input string to uppercase
	transform(searchString.begin(), searchString.end(), searchString.begin(), ::toupper);
	
	//Select File Size
	size = selectFileSize();

	//Select Permuted||Sorted
	permOrSort = selectPermutedOrSorted();

	//Select tree structure BST||RBT
	treeSelection = selectStructure();

	//Open file, save contents to temp
	temp = openFile(permOrSort,size,fileName);

	//Build Tree and Search
	buildAndSearch(treeSelection,temp,size,searchString);
	//foundNode can be used and tested here:

	cout << "Finished" << endl << endl;
	//"Run again?" dialog
	char ans;
	while (true) {
		cout << "Would you like to run the program again?(y/n)" << endl;
		cout << "ans: ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goto begin;
		}
		else if (ans == 'n' || ans == 'N') {
			exit(0);
		}
		else {
			system("CLS");
			cout << "!!Incorrect input!!" << endl;
		}
	}
	system("PAUSE");
    return 0;
}

