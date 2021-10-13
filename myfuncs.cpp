#include "myfuncs.h"


int PromptYN(std::string reply) {
	std::string acceptableAnswersYes[11] = { "YES", "yes", "Yes", "SURE", "sure", "Sure", "OK", "ok", "Y", "y" };
	std::string acceptableAnswersNo[16] = { "NO", "no", "No", "QUIT", "quit", "Quit", "STOP", "Stop", "stop", "TERMINATE", "terminate", "Terminate", "N", "n", "Q", "q" };
	for (int i = 0; i < size(acceptableAnswersYes); ++i) {
		if (reply == acceptableAnswersYes[i]) {
			return PLAY;
		}
	}
	for (int i = 0; i < size(acceptableAnswersNo); ++i) {
		if (reply == acceptableAnswersNo[i]) {
			return STOP;
		}
	}

	return ERROR;
}


void DrawHangman(int wrongGuesses) {
	const std::string BOARD0 = " -------|  \n"
		" |      |  \n"
		"        |  \n"
		"        |  \n"
		"        |  \n"
		"      -----\n";

	const std::string BOARD1 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		"        |  \n"
		"        |  \n"
		"      -----\n";

	const std::string BOARD2 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		" |      |  \n"
		"        |  \n"
		"      -----\n";

	const std::string BOARD3 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		"-|      |  \n"
		"        |  \n"
		"      -----\n";

	const std::string BOARD4 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		"-|-     |  \n"
		"        |  \n"
		"      -----\n";

	const std::string BOARD5 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		"-|-     |  \n"
		"/       |  \n"
		"      -----\n";

	const std::string BOARD6 = " -------|  \n"
		" |      |  \n"
		" O      |  \n"
		"-|-     |  \n"
		"/ \\     |  \n"
		"      -----\n";

	switch (wrongGuesses) {
	case 0:
		std::cout << BOARD0;
		break;
	case 1:
		std::cout << BOARD1;
		break;
	case 2:
		std::cout << BOARD2;
		break;
	case 3:
		std::cout << BOARD3;
		break;
	case 4:
		std::cout << BOARD4;
		break;
	case 5:
		std::cout << BOARD5;
		break;
	case 6:
		std::cout << BOARD6;
		break;
	}
}


void PrintGuesses(char usedLetters[], int used) {
	std::cout << "Letters Guessed: ";
	for (int i = 0; i < used; ++i) {
		std::cout << usedLetters[i] << "  ";
	}
	std::cout << "\n\n";
}

void PrintMaskedWord(std::string maskedWord) {
	for (int i = 0; i < maskedWord.length(); ++i) {
		std::cout << maskedWord[i] << " ";
	}
	std::cout << "\n\n";
}



std::string CreateMaskedWord(std::string wordToGuess) {
	std::string maskedWord = "";
	for (int i = 0; i < wordToGuess.length(); ++i) {
		maskedWord.push_back('_');
	}

	return maskedWord;
}


std::string UpdateMaskedWord(std::string maskedWord, std::string wordToGuess, char letterToGuess) {
	for (int i = 0; i < wordToGuess.length(); ++i) {
		if (letterToGuess == wordToGuess[i]) {
			maskedWord[i] = wordToGuess[i];
		}
	}
	return maskedWord;
}


std::string StrToUpper(std::string wordToGuess) {
	for (int i = 0; i < wordToGuess.size(); ++i) {
		wordToGuess[i] = toupper(wordToGuess[i]);
	}
	return wordToGuess;
}


int CheckWord(std::string wordToGuess, char letterToGuess) {
	int points = 0;
	for (int i = 0; i < wordToGuess.size(); ++i) {
		if (letterToGuess == wordToGuess[i]) {
			++points;
		}
	}
	return points;
}


bool BinarySearch(char usedLetters[], int used, char letterToGuess) {
	int low;
	int mid;
	int high;

	low = 0;
	high = used;
	while (high >= low) {
		mid = (high + low) / 2;
		//test
		//std::cout << low << "   " << mid << "   " << high << std::endl;
		if (letterToGuess > usedLetters[mid]) {
			low = mid + 1;
		}
		else if (letterToGuess < usedLetters[mid]) {
			high = mid - 1;
		}
		else if (letterToGuess == usedLetters[mid]) {
			//test
			//std::cout << letterToGuess << " was found at index " << mid;
			return true;
		}
	}
	return false;
}


void BubbleSort(char usedLetters[], int used) {
	for (int i = 0; i < used - 1; ++i) {
		bool swapped = false;
		for (int j = 0; j < (used - i - 1); ++j) {
			if (usedLetters[j] > usedLetters[j + 1]) {
				int temp = usedLetters[j];
				usedLetters[j] = usedLetters[j + 1];
				usedLetters[j + 1] = temp;

				swapped = true;
			}
		}
		if (swapped == false) {
			break;
		}
	}
}

void ClearArray(char usedLetters[], int used) {
	for (int i = 0; i < used; ++i) {
		usedLetters[i] = 0;
	}
}
