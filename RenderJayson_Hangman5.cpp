/*
Jayson Render
CSC 160 - 801
Hangman 5
Completed Hangman Game
July 18, 2021
*/


#include <iostream>
#include <string>
#include <fstream>
#include "randword.h"
#include "myfuncs.h"

int main() {
	const int MAX_WRONG = 6;
	std::string reply;
	int gameStatus = ERROR; //error state will keep game in a loop if player wants to play multiple rounds
	std::string wordToGuess;
	std::string maskedWord;
	char letterToGuess;
	char usedLetters[26] = {};
	int used;
	int lettersInWord;
	bool isUsed = true;

	int pointsToWin;
	int currentPoints;
	int wins = 0;
	int wrongGuesses;

	getWords("hangman.txt");
	while (gameStatus == ERROR or gameStatus == PLAY) {
		std::cout << "Do you want to play hangman? Y/N" << std::endl;
		std::cin >> reply;
		gameStatus = PromptYN(reply);
		if (gameStatus == STOP) {
			std::cout << "Okay, goodbye!\n";
			break;
		}
		else if (gameStatus == ERROR) {
			std::cout << "Error: Please enter 'yes' or 'no'. \n";
			continue; //will start loop over until user gives a proper answer
		}

		wordToGuess = getNextWord();

		//formats word to all uppercase for easier letter comparisons, creates masked word off of formatted string
		wordToGuess = StrToUpper(wordToGuess);
		maskedWord = CreateMaskedWord(wordToGuess);
		pointsToWin = wordToGuess.length();
		currentPoints = 0;
		used = 0;
		wrongGuesses = 0;

		//keeps asking for letters until player maxes out wrong guesses or guesses all letters
		while (wrongGuesses < MAX_WRONG && currentPoints < pointsToWin) {

			PrintMaskedWord(maskedWord);
			PrintGuesses(usedLetters, used);

			//keeps asking for letters if play gives a duplicate answer
			while (isUsed == true) {
				
				std::cout << "Guess a letter in the word: ";
				std::cin >> letterToGuess;
				letterToGuess = toupper(letterToGuess);
				
				isUsed = BinarySearch(usedLetters, used, letterToGuess);

				if (isUsed) {
					std::cout << letterToGuess << " has already been guessed. Try again!\n";
				}
				else {
					usedLetters[used] = letterToGuess;
					used++;
					break;
				}
			}
			
			BubbleSort(usedLetters, used);
			lettersInWord = CheckWord(wordToGuess, letterToGuess);
			
			if (lettersInWord > 0) {
				std::cout << letterToGuess << " is found in the word to guess!\n";
				maskedWord = UpdateMaskedWord(maskedWord, wordToGuess, letterToGuess);
				currentPoints += lettersInWord;
			}
			else {
				wrongGuesses++;
				std::cout << letterToGuess << " is NOT found in the word to guess" << std::endl;
			}
			DrawHangman(wrongGuesses);
			isUsed = true;
		}

		if (wrongGuesses == MAX_WRONG) {
			wins = 0;
			std::cout << "You lose!" << std::endl;
			std::cout << "The word you were trying to guess was: " << wordToGuess << std::endl;
			gameStatus = PLAY;
			ClearArray(usedLetters, used);

		}
		else if (currentPoints >= pointsToWin) {
			++wins;
			std::cout << "You win!" << std::endl << "You currently have a winning streak of " << wins << " games! Keep it up!" << std::endl;
			gameStatus = PLAY;
			ClearArray(usedLetters, used);
		}
	}
	return 0;
}