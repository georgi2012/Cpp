#include <iostream>
#include <new>


using std::cin;
using std::cout;
using std::nothrow;

const short moveX[] = { 0,1,1,-1,0,1,-1 ,-1 };
const short moveY[] = { 1,0,1,0,-1,-1,-1 ,1 };
const short movesNum = sizeof(moveX) / sizeof(short);
const unsigned MAX_WORD_SIZE = 100;

unsigned strLen(const char* word) {
	unsigned len = 0;
	while (word[len++]);
	return len - 1;
}

int strCmp(char* first, char* second) {
	while (*first && *first == *second) {
		++first;
		++second;
	}
	return *first - *second;
}

void strCpy(char* dest, const char* source) {
	while (*dest++ = *source++);
}

static void inputWords(int& wordCount, char**& words)
{
	char buffer[MAX_WORD_SIZE + 1] = { 0, };
	unsigned len = 0;
	std::cout << "Number of words:";
	std::cin >> wordCount;
	if (!cin || wordCount < 0) {
		std::cerr << "Invalid input .\n";
		throw - 1;
	}
	words = new (nothrow)char* [wordCount];
	if (!words) {
		std::cerr << "Couldn't allocate enough memory.\n";
		throw - 1;
	}

	for (unsigned i = 0; i < wordCount; i++) {
		cin >> buffer;
		len = strlen(buffer);
		words[i] = new (nothrow) char[len + 1];
		if (!words[i]) {
			for (unsigned j = 0; j < i; j++) {
				delete[] words[j];
			}
			delete[] words;
			std::cerr << "Couldn't allocate enough memory.\n";
			throw - 1;
		}
		strCpy(words[i], buffer);
	}

}


void sortWords(char**& words, const int wordCnt) {
	for (int i = 0; i < wordCnt - 1; i++) {
		for (int j = i + 1; j < wordCnt; j++) {
			if (strCmp(words[i], words[j]) > 0) {
				std::swap(words[i], words[j]);
			}
		}
	}
}


void getTableInput(short& dimension, char**& table) {
	cout << "\nTable size:";
	cin >> dimension;
	if (!cin || dimension < 2 || dimension>5) {
		std::cout << "Invalid input!";
		throw - 1;
	}
	table = new (nothrow) char* [dimension];
	if (!table) {
		std::cout << "Not enough memory.\n";
		throw - 1;
	}

	for (unsigned i = 0; i < dimension; i++) {
		table[i] = new (nothrow) char[dimension];
		if (!table[i]) {
			for (unsigned j = 0; j < i; j++) {
				delete[] table[j];
			}
			delete table;
			std::cout << "Not enough memory.\n";
			throw - 1;
		}
		for (unsigned j = 0; j < dimension; j++) {
			cin >> table[i][j]; //input
		}
	}
}

void deleteInfo(char**& words, const int wordCnt, short dim = 0, char** table = nullptr) {
	for (unsigned i = 0; i < wordCnt; i++) {
		delete[] words[i];
	}
	delete[] words;
	if (table) {
		for (unsigned i = 0; i < dim; i++) {
			delete[] table[i];
		}
		delete[] table;
	}

}

bool searchForWord(const char* word, const short dim, char**& table, bool isChecked[][5], const short X, const short Y) {
	
	if (!*word) {
		return true;
	}
	isChecked[X][Y] = true;
	bool isFound = 0;

	for (unsigned j = 0; j < movesNum; j++) {
		if (X+moveX[j] < dim && Y+moveY[j] < dim && X +moveX[j]>= 0  && moveY[j]+Y >= 0 &&
			!isChecked[X+moveX[j]][Y+moveY[j]] && table[X+moveX[j]][Y+moveY[j]] == *word) {
			if (searchForWord(word + 1, dim, table, isChecked, X+moveX[j], Y+moveY[j])) {
				isFound = true;
				break;
			}
		}
	}
	isChecked[X][Y] = false;
	return isFound;
}

static bool findStarter(const char* word, const short dim, char**& table, bool isChecked[][5]) {

	bool isFound = false;
	for (unsigned i = 0; i < dim; i++) {
		for (unsigned j = 0; j < dim; j++) {
			if (*word == table[i][j]) {
				if (searchForWord(word+1, dim, table, isChecked, i, j)) {
					isFound = true;
					break;
				}
			}
		}
	}
	return isFound;
}

static void printWord(char* word) {
	unsigned len = 0;
	while (word[len]) {
		std::cout << word[len++];
	}
	std::cout << "\n";
}

static void printLongest(char**& words, const int wordsCnt,char**& table, const short dim) {
	bool isChecked[5][5] = { 0 };
	bool isFound = false;
	std::cout << "Number of words found: " << wordsCnt << "\n";
	if (wordsCnt == 0) return;
	std::cout << "Longest word(s):\n";
	for (unsigned i = 0; i < wordsCnt; i++) {
		isFound = findStarter(words[i], dim, table, isChecked);
		if (isFound ) {
			printWord(words[i]);
			if (i + 1 < wordsCnt && strLen(words[i + 1]) < strLen(words[i])) {
				break;
			}
		}
		
	}

}

int main() {
	int wordCount = 0;
	short tableDim = 0;
	char** words = nullptr;
	char** table = nullptr;
	//
	try {
		inputWords(wordCount, words);
	}
	catch (const int& e) {
		return -1;
	}
	//
	sortWords(words, wordCount);
	//
	try {
		getTableInput(tableDim, table);
	}
	catch (const int& e) {
		deleteInfo(words, wordCount);
		return -1;
	}
	//
	printLongest(words, wordCount, table, tableDim);
	//
	deleteInfo(words, wordCount, tableDim, table);
	//
	return 0;
}