
#ifndef MYFUNCS_H
#define MYFUNCS_H

#include <string>
#include <iostream>
#include <cstdlib>

#define PLAY 1
#define STOP 0
#define ERROR -1

int PromptYN(std::string reply);

void DrawHangman(int wrongGuesses);

void PrintGuesses(char usedLetters[], int used);

void PrintMaskedWord(std::string maskedWord);

std::string CreateMaskedWord(std::string wordToGuess);

std::string UpdateMaskedWord(std::string maskedWord, std::string wordToGuess, char letterToGuess);

std::string StrToUpper(std::string str);

int CheckWord(std::string wordToGuess, char letterToGuess);

bool BinarySearch(char usedLetters[], int used, char letterToGuess);

void BubbleSort(char usedLetters[], int used);

void ClearArray(char usedLetters[], int used);
#endif