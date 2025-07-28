#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include <limits>
#include <locale>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#include<vector>
#endif
using namespace std;

int main() {

    setlocale(LC_ALL, ""); // Set the locale to the user's default locale

#ifdef _WIN32
    // Configure the console for Unicode encoding on Windows
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
#endif

    wstring filename = L"es-en.csv"; // Default dictionary filename
    unsigned int max_results = 0; // Maximum search results to display

    // Print welcome message and prompt for a dictionary filename
    wcout << L"Welcome to the line-by-line search program (built to search span-english dictionary - for SPAN-420 UM-DEARBORN)\n";
    wcout << L"By Demetrius Johnson (Meech)";
    wcout << L"Input a dictionary - or any txt or csv - filename to do line-by-line word search\n";
    wcout << L"(make sure the file is in the same\ndirectory as where you launched this program, or specify full path including filename):\nEnter file name:";
    getline(wcin, filename);

    // Prompt for the maximum number of search results to display
    wcout << L"Enter the MAX number of results you want displayed (lines in the file that contain your search word): ";
    wcin >> max_results;

    //clear input buffer and ignore any extra char in the buffer
    wcin.clear();
    wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    // Open the dictionary file
    wifstream dictionary(filename, ios::in);
    if (!dictionary.is_open()) {
        wprintf(L"\"%s\" dictionary file not found or opened, program will exit\n", filename.c_str());
        system("pause");
        return -1;
    }

    // Reserve memory for the vector (to increase the speed of the program by avoiding having to resize the vector)
    const unsigned int reserved_memory = 70000; // Change to the expected number of lines in the file
    vector<wstring> lines;
    lines.reserve(reserved_memory);

    //enhance file reading performance for this specific application by using line buffering instead of block buffering:
    //std::wcin.tie(nullptr); // Break the tie between wcin and wcout
    //std::ios_base::sync_with_stdio(false); // Set the buffering mode to line buffered

    // Read the entire file into memory
    wstring line;
    while (getline(dictionary, line)) {
        //emplace_back is used instead of push_back to avoid unnecessary copying of elements.
        //Additionally, move is used to move the contents of line into the vector, 
        //rather than copying it.This can improve performance by avoiding unnecessary copies of the wstring objects
        lines.emplace_back(move(line));
    }
    dictionary.close();



    wstring word; // Word to search for
    unsigned int count = 0; // Number of search results found
    unsigned int line_count = 0; // Current line number in the file

    while (true) {
        // Prompt for a word to search for
        wcout << L"Input a word to search for (q to quit): ";
        getline(wcin, word);
        if (word == L"q") { break; }

        // Search for the word in the memory
        for (const auto& current_line : lines) {
            line_count++;
            if (current_line.find(word) != wstring::npos) {
                count++;
                wcout << L"search_result_" << count << L" [line#_" << line_count << L"]: " << current_line << endl;
                if (count >= max_results) {
                    break;
                }
            }
        }

        // Display a message if the word was not found in the file
        if (count == 0) {
            wprintf(L"************\"%s\" NOT FOUND IN \"%s\" FILE**********\n***IF ERROR SUSPECTED, RELAUNCH PROGRAM AND CHECK INPUT********\n", word.c_str(), filename.c_str());
            wcout << endl;
        }
        else {
            wprintf(L"\n-------------------END OF SEARCH RESULTS FOR \"%s\" IN \"%s\" (MAX SET TO %d)----------------\n\n", word.c_str(), filename.c_str(), max_results);
        }

        // Reset variables for next loop:
        count = 0;
        line_count = 0;
    }

    // Exit program
    wcout << L"program exiting...\n";
    system("pause");
    return 0;
}
