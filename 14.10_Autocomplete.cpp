// 14.10_Autocomplete.cpp 
//-----------------------------------------------------------------------
//  Header      : -
//  Created     : 05.02.2023
//  Author      : Vladimir Lapshov
//  Description : Simple console typesetter utility with autocompletion function. 
//				  Skillfactory C++ / 14.10 homework 
//				  Еhe program is written and tested under win10 / VS2019 / C++ 14
//-----------------------------------------------------------------------

#include <iostream>
#include <windows.h> // WinApi header for colored text
#include <conio.h> // used for _getch(): char input without enter
#include "string.h"

#include "Trie.h"
 
const int YELLOW = 14;
const int GREEN = 10;
const int WHITE = 15;
const int RED = 4;
const int CYAN = 11;
const int MAGENTA = 13;

// backspace from console
void backspace (int count){
    for (int i = 0; i < count; i++)
        std::cout << '\b' << " " << '\b';
}

bool symbolAcceptable(char symbol) {
	return (symbol <= 'z' && symbol >= 'a');
}

int main()
{
	// Construct dictionary trie
	Trie dictionary;
	TrieNode* dictRoot = dictionary.getRoot();
	std::string keys[] = { "in", "the", "town", "where", "i", "was", "born",
							"lived", "a", "man", "who", "sailed", "the", "sea",
							"and", "he", "told", "us", "of", "his", "life",
							  "land", "of", "submarines"
						 };
	int n = sizeof(keys) / sizeof(keys[0]);
	for (int i = 0; i < n; i++)
		dictionary.insert(dictRoot, keys[i]);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	std::cout << "\t\t ** Lazy Ass typesetter ** " << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
	std::cout << "Type a message. \"Enter\" or \"Space bar\" key - to accept autocompletion, \"Esc\" - finish and exit. " << std::endl;
		
    bool typing = true; // enter the text while true
	std::string word; //current word buffer
	//size_t wordLength = 0;
	std::string restOfWord; // the remains of the word from dictionary for autocompletion
	bool autocompletionAccepted = true; // whether restOfWord accepted by user or not

	char buttonPressed;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	while (typing) {
		buttonPressed = _getch(); // unbuffered single char input
		{
			switch (buttonPressed)
			{
			case 8: // backspace
				if (word.length() > 0) {
					backspace(1);
					word.erase(word.end()-1);
					restOfWord = "";
				}				
				break;
			case 13: // Enter
				// if a part of the word was suggested for autocompletion,
				// accept the autocompletion and change it's color from green to yellow
				if (restOfWord.length() > 0) {
					backspace(restOfWord.length());
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					std::cout << restOfWord;
				}
				word = "";
				restOfWord = "";
				autocompletionAccepted = true;
				std::cout << std::endl;
				break;
			case 27: // escape
				typing = false;
				break;
			case 32: // space
				// if a part of the word was suggested for autocompletion,
				// accept the autocompletion and change it's color from green to yellow
				if (restOfWord.length() > 0) {
					backspace(restOfWord.length());
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					std::cout << restOfWord;
				}
				word = "";
				restOfWord = "";
				autocompletionAccepted = true;
				std::cout << " ";
				break;
			default:
				if (!symbolAcceptable(buttonPressed)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					std::cout << std::endl << "Only english lowercase symbols are allowed!" << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
					break;
				}
				// if suggested autocompletion was not confirmed by Space оr Enter,
				// remove suggested restOfWord from the word and from console
				if (autocompletionAccepted == false) {
					if (restOfWord.length() > 0) {
						backspace(restOfWord.length());
						word.erase(word.length() - restOfWord.length(), restOfWord.length());
					}
				}
				word += buttonPressed;
				std::cout << buttonPressed;
				restOfWord = dictionary.completeWordByPrefix(word);
 				if (restOfWord.length() > 0) {
					// now suggested restOfWord should be confirmed by Space оr Enter
					// othervise it will be erased next iteration
					autocompletionAccepted = false; 
					word += restOfWord;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
					std::cout << restOfWord;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				}
				break;
			}
		}		
	}

	return 0;
}

