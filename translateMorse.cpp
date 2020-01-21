/*
Name: Logan Ziemann
Class: CPSC122, Spring 2020
Date: January 14, 2020
Programming Assignment: PA1
Description: This program converts english text from a .txt file to morse code in a .txt file and vice-versa.
	     It also computes the total number of characters that are converted and displays that at the end of the .txt files as well.
Notes: I used cplusplus.com as a reference.
*/

#include "functions.h"
int main(){
	morseLibrary();		// opens morse string library
	
	string userInput;
	
	cout << "CMD> ";	
	cin >> userInput;
	
	ofstream outFile;
	ifstream inFile;
	
	if(userInput.at(1) == 'm'){		// converts english to morse
		openInputFile(inFile, "english.txt");
		openOutputFile(outFile, "morse.txt");
		processEngFile(inFile, outFile);
		outFile.close();
		inFile.close();
		
	} else if(userInput.at(1) == 't'){		// converts morse to english
		openOutputFile(outFile, "english.txt");
		openInputFile(inFile, "morse.txt");
		processMorseFile(inFile, outFile);
		inFile.close();
		outFile.close();
		
	} else {
		cout << "invalid input. try again." << endl;
	
	}
	
	return 0;
}
