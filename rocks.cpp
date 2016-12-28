// Prateek Singh
// Project 5
// Professor Smallberg
// Due: 11/17/15 9:00 pm


#include <cstring>
#include <iostream>
#include "utilities.h"
using namespace std;

bool isValidProbe(const char given[])
{
	if (strlen(given) < 4 || strlen(given) > 6)
	{
		return false;
	}

	for (int i = 0; i < strlen(given); i++)
	{
		if (!isalpha(given[i]) || !islower(given[i]))
		{
			return false;
		}
	}

	return true;
}


int manageOneRound(const char words[][7], int nWords, int wordnum)
{

	int numberOfTries = 1;
	while (true)
	{

		if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
		{
			return -1;
		}

		// Read in a probe word
		cout << "Probe word: ";
		char givenProbe[100];
		cin.getline(givenProbe, 100);

		// validate probe word for number of digits and all lowercase
		if (!isValidProbe(givenProbe))
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}
		if (strcmp(givenProbe, words[wordnum]) == 0)
		{
			return numberOfTries;
		}
		// validate probe word for existence in dictionary

		bool wordExists = false;

		for (int i = 0; i < nWords; i++)
		{
			if (strcmp(givenProbe, words[i]) == 0)
			{
				wordExists = true;
			}
		}

		if (!wordExists)
		{
			cout << "I don't know that word." << endl;
			continue;
		}


		// start finding the correct values for rocks and pebbles

		int rocks = 0;
		int pebbles = 0;

		// can only make comparisons after knowing whether secret or probe word is longer

		int lettersToLoop;

		if (strlen(givenProbe) > strlen(words[wordnum]))
		{
			lettersToLoop = strlen(givenProbe);
		}

		else
		{
			lettersToLoop = strlen(words[wordnum]);
		}

		// calculate number of rocks and fill up the usedPosition array for spots that are paired with rocks

		// array for positions that do not need to be checked in the secret word

		int usedSecretPos[7] = { -1, -1, -1, -1, -1, -1, -1 };
		int whereToPut = 0;

		// array for positions that do not need to be checked int the probe word

		int usedProbePos[7] = { -1, -1, -1, -1, -1, -1, -1 };
		int whereToPutProbe = 0;

		for (int i = 0; i < lettersToLoop; i++)
		{
			if (givenProbe[i] == words[wordnum][i])
			{
				rocks++;
				usedSecretPos[whereToPut] = i;
				whereToPut++;
				usedProbePos[whereToPutProbe] = i;
				whereToPutProbe++;
			}
		}

		// now calculating number of pebbles

		int k = 0;
		// looping through characters of probe word
		while (k < strlen(givenProbe))
		{
			// boolean to break out for k

			bool breakOutMain = false;
			for (int z = 0; z < whereToPutProbe; z++)
			{
				if (k == usedProbePos[z])
				{
					k++;
					breakOutMain = true;
					break;
				}
			}

			if (breakOutMain)
			{
				continue;
			}
			
			int j = 0;
			// looping through characters of secret word
			while (j < strlen(words[wordnum]))
			{
				bool breakOut = false;
				// looping through usedPositions
				for (int z = 0; z < whereToPut; z++)
				{
					if (j == usedSecretPos[z])
					{
						j++;
						breakOut = true;
						break;
					}
				}

				if (breakOut)
				{
					continue;
				}

				bool breakSecond = false;
				if (!(j < strlen(words[wordnum]))) break;
				
				bool repeats = false;
				for (int z = 0; z < whereToPut; z++)
				{
					if (k == usedProbePos[z])
					{
						repeats = true;
						break;
					}
				}
				
				if (!repeats && givenProbe[k] == words[wordnum][j])
				{
					
					pebbles++;
					usedSecretPos[whereToPut] = j;
					whereToPut++;
					j++;
					breakSecond = true;
					break;
				}
				if (breakSecond) break;
				j++;
			}

			k++;
		}

		numberOfTries++;

		 cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
	}
}

int main()
{

	// setup for errors and word list

	const int MAXWORDS = 9000;

	char wordList[MAXWORDS][MAXWORDLEN + 1];

	int numWords = loadWords(wordList, 9000);

	// just a check
	//cout << numWords << endl;

	if (numWords <= 0)
	{
		cout << "No words were loaded, so I can't play the game." << endl;

		return 0;

	}

	// now actually begin playing the game

	cout << "How many rounds do you want to play? ";

	// read in number of rounds that user wants to play
	int numRounds;
	cin >> numRounds;
	cin.ignore(10000, '\n');

	if (numRounds <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		
		return 0;
	}

	// initialize some statistics that span multiple rounds

	int minimumTries = 0;
	int maximumTries = 0;
	double totalTries = 0.0;	// created as a double so that divison for average yields a double answer
	double averageTries = 0.0;


	for (int i = 1; i <= numRounds; i++)
	{
		int positionOfSecret = randInt(0, numWords - 1);
		
		// just a check
		//cout << wordList[positionOfSecret] << endl;

		cout << endl << "Round " << i << endl;
		cout << "The secret word is " << strlen(wordList[positionOfSecret]) << " letters long." << endl;

		int numTries = manageOneRound(wordList, numWords, positionOfSecret);

		// first output line at the end of the round

		if (numTries == 1)
		{
			cout << "You got it in 1 try." << endl;
		}

		else
		{
			cout << "You got it in " << numTries << " tries." << endl;
		}

		// output line for average, max, and min
		if (i == 1)
		{
			minimumTries = numTries;
			maximumTries = numTries;
			averageTries = numTries;
			totalTries += numTries;
		}

		else
		{
			if (numTries <= minimumTries)
			{
				minimumTries = numTries;
			}

			if (numTries >= maximumTries)
			{
				maximumTries = numTries;
			}

			totalTries += numTries;

			averageTries = totalTries / i;
		}

		// clean output

		cout.setf(ios::fixed);
		cout.precision(2);

		cout << "Average: " << averageTries << ", minimum: " << minimumTries << ", maximum: " << maximumTries << endl;
	}
}
