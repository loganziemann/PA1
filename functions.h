/*
Name: Logan Ziemann
Class: CPSC122, Spring 2020
Date: January 14, 2020
Programming Assignment: PA1
Description: This program converts english text from a .txt file to morse code in a .txt file and vice-versa.
	     It also computes the total number of characters that are converted and displays that at the end of the .txt files as well.
Notes: I used cplusplus.com as a reference.
*/

//any #include, using namespace, and all function prototypes

#include <iostream>													// included libraries
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void morseLibrary();												// void return type function(s)
void processMorseFile(ifstream& inFile, ofstream& outFile);
void processEngFile(ifstream& inFile, ofstream& outFile);
void openInputFile(ifstream&, string fname);
void openOutputFile(ofstream&, string fname);

string engToMorse(char ch);											// string return type function(s)

char morseToEng(string morse);										// char return type function(s)
