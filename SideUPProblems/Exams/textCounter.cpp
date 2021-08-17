#include<iostream>
#include <new>

using std::cin;
using std::cout;
using std::nothrow;

const unsigned MAX_SIZE=1000;

unsigned strLen(const char* const word) {
	size_t len = 0;
	while (word[len] && word[len]!=' ') {
		++len;
	}
	return len;
}

int strCmp(const char* first, char* second) {
	while (*first && *second==*first) {
		++first;
		++second;
		if (*second == ' ') {
			(*second) = '\0';
		}
	}
	return *first - *second;

}

void addNewWord(char**& words,  size_t& diffWordsCnt, char* newWord,short*& wordsCnt) {

	char** newWords = new (nothrow) char* [diffWordsCnt + 1];
	if (!newWords) {
		std::cerr << "Problem allocating enough memory for " << diffWordsCnt + 1;
		return;
	}
	for (size_t i = 0; i < diffWordsCnt; i++) {
		newWords[i] = words[i];
	}
	newWords[diffWordsCnt] = new (nothrow) char[strLen(newWord)+1];
	if (!newWords) {
		std::cerr<< "Problem allocating enough memory for " << strLen(newWord) + 1;
		delete[] newWords;
		return;
	}
	size_t index = 0;
	while (index < strLen(newWord)) {
		newWords[diffWordsCnt][index] = *(newWord+index); //copy
		++index;
	}
	newWords[diffWordsCnt][index] = '\0';
	
	short* newWordsCnt = new (nothrow) short[diffWordsCnt + 1];
	if (!newWordsCnt) {
		delete[] newWords[diffWordsCnt];
		delete[] newWords;
		std::cerr << "Problem allocating enough memory for " << diffWordsCnt;
		return;
	}
	for (unsigned i = 0; i < diffWordsCnt; i++) {
		newWordsCnt[i] = wordsCnt[i];
	}
	newWordsCnt[diffWordsCnt++] = 1;


	delete[] words;
	delete[] wordsCnt;
	wordsCnt = newWordsCnt;
	words = newWords;
}

void addWord(char**& words, size_t& diffWordsCnt, char* newWord, short*& wordsCnt)
{
	bool isFound = false;
	for (size_t i = 0; i < diffWordsCnt;  i++) {
		if (strCmp(words[i], newWord)==0) {
			wordsCnt[i]++;
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		addNewWord(words,  diffWordsCnt, newWord, wordsCnt);
	}

}
void countWords(char**& words, size_t& diffWordsCnt,char* text,short*& wordsCnt)
{
	char* wordStart =text;
	char* wordEnd = text;
	size_t index = 0;
	while (text[index]) {
		if (text[index] != ' ') {
			wordEnd++;
		}
		else if (text[index] == ' ' && wordStart >= wordEnd) {
			++wordStart;
			++wordEnd;
		}
		else { //wordStart<wordEnd
			++wordEnd;
			addWord(words, diffWordsCnt, wordStart, wordsCnt);
			wordStart = wordEnd;
		}
		
		++index;
	}
	addWord(words, diffWordsCnt, wordStart, wordsCnt);
}

static void print(char**& words, const short* nums, const size_t num) {
	for (unsigned i = 0; i < num; i++) {
		cout << words[i] << " - " << nums[i] << std::endl;
	}
}

int main() {
	char buffer[MAX_SIZE + 1];
	char** words = nullptr;
	short* wordsCount = nullptr;
	size_t diffWordsCnt = 0;
	//
	cin.getline(buffer, MAX_SIZE);
	if (!cin) {
		std::cerr << "Invalid input.\n";
		return -1;
	}
	//
	countWords(words, diffWordsCnt, buffer, wordsCount);
	//
	print(words, wordsCount, diffWordsCnt);
	//
	for (unsigned i = 0; i < diffWordsCnt; i++) {
		delete[] words[i];
	}
	delete[] words;
	delete[] wordsCount;

	return 0;
}