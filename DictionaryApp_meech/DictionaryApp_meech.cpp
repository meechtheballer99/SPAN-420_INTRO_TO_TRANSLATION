// DictionaryApp_meech.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Author: Demetrius Johnson
//Purpose: line-by-line word search in span-english dictionary (txt/csv files) - for SPAN-420 UM-DEARBORN
//Date created: 3/29/23
//Date modified: 3/29/23

//note: I will make ints unsigned whenever possible so they can have a max positive value.
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;


int main()
{
	fstream dictionary;
	string filename = "es-en.csv";
	unsigned int max_results = 0;
	cout << "Welcome to the line-by-line search program (built to search span-english dictionary - for SPAN-420 UM-DEARBORN)\n";
	cout << "By Demetrius Johnson (Meech)";
	cout << "Input a dictionary - or any txt or csv - filename to do line-by-line word search\n";
	cout << "(make sure the file is in the same\ndirectory as where you launched this program, or specify full path including filename):\nEnter file name:";
	cin >> filename;

	cout << "Enter the MAX number of results you want displayed (lines in the file that contain your search word): ";
	cin >> max_results;

	//clear cin buffer since I will use it later to get full lines from user.
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	dictionary.open(filename, ios::in);
	if (!dictionary.is_open()) {
		printf("\"%s\" dictionary file not found or opened, program will exit\n", filename.c_str());
		system("pause");
		return -1;
	}

	string word;
	string line;
	unsigned int count = 0;
	unsigned int line_count = 0;
	while (true) {

		cout << "Input a word to search for (q to quit): ";
		//flush and clear cin buffer for next user input (so we can acquire a full line, need to use getline)

		getline(cin, word);
		if (word == "q") { break; }
		while (getline(dictionary, line) && count < max_results) {
			line_count++;
			//npos is a static member constant value with the greatest possible value for 
			// an element of type size_t. This value, when used as the value for 
			// a len (or sublen) parameter in string's member functions, 
			// means "until the end of the string". 
			//As a return value, it is usually used to indicate no matches.
			if (line.find(word) != std::string::npos) {
				count++;
				cout << "search_result_" << count << " [line#_" << line_count << "]: " << line << endl;
			}

		}
		if (count == 0) {
			printf("************\"%s\" NOT FOUND IN \"%s\" FILE**********\n***IF ERROR SUSPECTED, RELAUNCH PROGRAM AND CHECK INPUT********\n", word.c_str(), filename.c_str());
			cout << endl;
		}
		else
			printf("\n-------------------END OF SEARCH RESULTS FOR \"%s\" IN \"%s\" (MAX SET TO %d)----------------\n\n", word.c_str(), filename.c_str(), max_results);
		//need to clear EOF flag, then seek back to beginning of the file
		dictionary.clear();
		dictionary.seekg(0, ios::beg);
		//reset word found counter/result number and line number tracker:
		count = 0;
		line_count = 0;

	}

	cout << "program exiting...\n";
	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file