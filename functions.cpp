/*
Name: Logan Ziemann
Class: CPSC122, Spring 2020
Date: January 14, 2020
Programming Assignment: PA1
Description: This program converts english text from a .txt file to morse code in a .txt file and vice-versa.
	     It also computes the total number of characters that are converted and displays that at the end of the .txt files as well.
Notes: I used cplusplus.com as a reference.
*/

// every function definition except main
#include "functions.h"		// reads through prototypes in functions.h

string morseStrings[91];

/*************************************************************
 * Function: openInputFile()
 * Date Created: 1/16/20
 * Date Last Modified: 1/16/20
 * Description: opens files for input and performs error checking.
 * Input parameters: input file and input file name
 * Returns: informs user of fail if file fails to open, otherwise nothing
 * Pre: no input file is opened
 * Post: either input file is opened or user is informed of failure
 *************************************************************/

void openInputFile(ifstream& inFile, string fname){		// opens input file, checks to see if opened correctly
	inFile.open(fname);
	if(!inFile.is_open()){
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

/*************************************************************
 * Function: openOutputFile()
 * Date Created: 1/16/20
 * Date Last Modified: 1/16/20
 * Description: opens files for output and performs error checking.
 * Input parameters: output file and output file name
 * Returns: informs user of fail if file fails to open, otherwise nothing
 * Pre: no input file is opened
 * Post: either input file is opened or user is informed of failure
 *************************************************************/

void openOutputFile(ofstream& outFile, string fname){	// opens output file, checks to see if opened correctly
	outFile.open(fname);
	if(!outFile.is_open()){
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

/*************************************************************
 * Function: translateToMorse()
 * Date Created: 1/14/20
 * Date Last Modified: 1/19/20
 * Description: converts lowercase to uppercase if needed, translates a single english character into a single morse string
 * Input parameters: single english character
 * Returns: single morse string
 * Pre: only english letter
 * Post: morse string
 *************************************************************/

string translateToMorse(char ch){
	int ascii = (int)ch;
	
	if(ascii > 90){		// checks if char is lowercase, then converts to uppercase if need be
		ascii = ascii - 32;	
	}
	
	string morse = morseStrings[ascii];		// assigns morse string to char
	
	return morse;
}

/*************************************************************
 * Function: translateToEng()
 * Date Created: 1/14/20
 * Date Last Modified: 1/19/20
 * Description: translates a single morse string into a single english character
 * Input parameters: single morse string
 * Returns: single english character
 * Pre: only morse string
 * Post: english letter
 *************************************************************/

char translateToEng(string morse){
	char engChar;
	int ascii;
	
	for(int i = 0; i < 91; i++){	// searches through morseStrings array for a morse string that matches the input, returns ascii value of english char
		if(morseStrings[i] == morse){
			ascii = i;
		}
	}
	
	engChar = (char)ascii;	// converts ascii value to char
	
	if(morse == "&"){	// checks if morse string equals ampersand, chosen special character for a word space (since stringstream ignores whitespace)
		engChar = ' ';
	}
	
	return engChar;
}

/*************************************************************
 * Function: processMorseFile()
 * Date Created: 1/16/20
 * Date Last Modified: 1/18/20
 * Description: reads entire morse file, translates to english, and writes the english to english file. 
 * 				also counts number of morse strings and whitespace (space and newline) translated
 * Input parameters: input file and output file
 * Returns: nothing
 * Pre: user only has morse code
 * Post: user now has both morse code and its english translation
 *************************************************************/

void processMorseFile(ifstream& inFile, ofstream& outFile){
	string line;
	string letter;
	istringstream iss;
	int letterc = 0;
	int newline = 0;
	int space = 0;
	int dspace = 0;
	int counter = 0;
	
	while(!inFile.eof()){
		getline(inFile, line);
		
		for(int i = 0; i < line.size(); i++){	// places ampersand to mark a space between words
			if(line[i] == ' ' && line[i+1] == ' '){
				line.insert(i+1, 1, '&');
				dspace += 2;
			}
		}
		
		if(inFile.good()){
			iss.clear();
			iss.str(line);
			while(iss.good()){
				iss >> letter;
				if(letter != ""){
					outFile << translateToEng(letter);	// converts morse to a char and stores it in the output file
					letter = "";
					letterc++;
					space++;
				}
			}
			
			outFile << endl;	// next line starts on new line, therefore counter increments
			newline++;
		}
	}
	
	letterc -= (dspace/2);
	space -= (dspace+newline);
	counter += letterc;
	counter += newline;
	counter += space;
	counter += dspace;
	cout << "Total morse strings converted successfully (including newline and white spaces): " << (counter) << endl;
	counter = 0;
}

/*************************************************************
 * Function: processEngFile()
 * Date Created: 1/16/20
 * Date Last Modified: 1/18/20
 * Description: reads entire english file, translates to morse, and writes the morse to morse file. 
 * 				also counts number of english characters and whitespace (space and newline) translated
 * Input parameters: input file and output file
 * Returns: nothing
 * Pre: user only has english
 * Post: user now has both english and its morse code translation
 *************************************************************/

void processEngFile(ifstream& inFile, ofstream& outFile){
	string line;
	char letter;
	int counter = 0;

	while(!inFile.eof()){
		getline(inFile, line);
		
		if(inFile.good()){
			for(int i = 0; i <= line.size(); i++){
				letter = line[i];
				if(i == line.size()){	// indicates char at line's end (newline)
					outFile << endl;
					counter++;
				} else if(letter == ' '){	// indicates space = new word, therefore second space added to morse
					outFile << " ";
					counter++;
				} else {	// indicates no space or endl, therefore is a letter that is translated to morse code w/ space to indicate separate letters
					string output = translateToMorse(letter);
					outFile << output;
					if(i != line.size()-1){
						outFile << " ";
					}
					
					counter++;
				}
			}
		}
	}
	
	cout << "Total characters converted successfully (including newline and white spaces): " << counter << endl;
	counter = 0;
}

/*************************************************************
 * Function: morseLibrary()
 * Date Created: 1/14/20
 * Date Last Modified: 1/14/20
 * Description: stores every morse string in the morseStrings array 
 * 				at the index equal to the ascii value of the letter the morse translates to.
 * Input parameters: n/a
 * Returns: n/a
 * Pre: morse code strings unknown
 * Post: rest of code now knows ascii --> morse code translation
 *************************************************************/

void morseLibrary(){		// stores every morse string within the morseStrings array
	morseStrings[65] = ".-";	//A
	morseStrings[66] = "-...";	//B
	morseStrings[67] = "-.-.";	//C
	morseStrings[68] = "-..";	//D
	morseStrings[69] = ".";		//E
	morseStrings[70] = "..-.";	//F
	morseStrings[71] = "--.";	//G
	morseStrings[72] = "....";	//H
	morseStrings[73] = "..";	//I
	morseStrings[74] = ".---";	//J
	morseStrings[75] = "-.-";	//K
	morseStrings[76] = ".-..";	//L
	morseStrings[77] = "--";	//M
	morseStrings[78] = "-.";	//N
	morseStrings[79] = "---";	//O
	morseStrings[80] = ".--.";	//P
	morseStrings[81] = "--.-";	//Q
	morseStrings[82] = ".-.";	//R
	morseStrings[83] = "...";	//S
	morseStrings[84] = "-";		//T
	morseStrings[85] = "..-";	//U
	morseStrings[86] = "...-";	//V
	morseStrings[87] = ".--";	//W
	morseStrings[88] = "-..-";	//X
	morseStrings[89] = "-.--";	//Y
	morseStrings[90] = "--..";	//Z

	morseStrings[48] = "-----";	//0
	morseStrings[49] = ".----";	//1
	morseStrings[50] = "..---";	//2
	morseStrings[51] = "...--";	//3
	morseStrings[52] = "....-";	//4
	morseStrings[53] = ".....";	//5
	morseStrings[54] = "-....";	//6
	morseStrings[55] = "--...";	//7
	morseStrings[56] = "---..";	//8
	morseStrings[57] = "----.";	//9
}
