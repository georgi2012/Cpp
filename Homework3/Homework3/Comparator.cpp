#include "interface.h"
#include <excpt.h>

Comparator::Comparator(const Comparator& other)
	:f1AllWordsCnt(other.f1AllWordsCnt),f2AllWordsCnt(other.f2AllWordsCnt), commonWordsInFiles(other.commonWordsInFiles)
{
}

Comparator::Comparator(Comparator&& other) noexcept
	:f1AllWordsCnt(other.f1AllWordsCnt),f2AllWordsCnt(other.f2AllWordsCnt),commonWordsInFiles(other.commonWordsInFiles)
{
}

Comparator& Comparator::operator=(const Comparator& other)
{
	f1AllWordsCnt = other.f1AllWordsCnt;
	f2AllWordsCnt = other.f2AllWordsCnt;
	commonWordsInFiles = other.commonWordsInFiles;
	return *this;
}

Comparator& Comparator::operator=(Comparator&& other) noexcept
{
	f1AllWordsCnt = other.f1AllWordsCnt;
	f2AllWordsCnt = other.f2AllWordsCnt;
	commonWordsInFiles = other.commonWordsInFiles;
	return *this;
}

ComparisonReport Comparator::compare(std::istream& a, std::istream& b)
{ //a and b should be tested already?
	if (!a || !b)
	{
		throw std::logic_error("Cant read data stream.");
	}
	//
	a.seekg(0, std::ios::end);
	size_t sizeOfA = a.tellg();
	a.seekg(0, std::ios::beg);
	b.seekg(0, std::ios::end);
	size_t sizeOfB = b.tellg();
	b.seekg(0, std::ios::beg);
	//In order to have better access/insert time for our unordered_map that uses buckets, we will try to decide what is the 
	//expected number of (different) words that will be inserted by taking it's size and divide it to a constant 
	ComparisonReport cr;
	WordsMultiset first(ceil(sizeOfA / (AVG_WORD_LEN* 8.0)));//Multiset for stream a with size of bytes of A/ avg word len
	WordsMultiset second(ceil(sizeOfB / (AVG_WORD_LEN * 8.0)));//-- for stream b
	string word;
	//
	std::cout << "Reading data from first file...\n";
	while (a >> word) {
		first.add(word);
		++f1AllWordsCnt;
	}
	std::cout << "Reading data from second file...\n";
	while (b >> word) {
		second.add(word);
		++f2AllWordsCnt;
	}
	std::cout << "Data loaded and being processed...\n";
	//
	bool firstIsSmaller = first.countOfUniqueWords() < second.countOfUniqueWords();
	WordsMultiset* smallerMSet = firstIsSmaller ? &first : &second;//we take the set with fewer words
	WordsMultiset* biggerMSet = !firstIsSmaller ? &first : &second; //we take the set with more words

	for (auto el : smallerMSet->umap) {
		auto item = biggerMSet->umap.find(el->key);
		if (item) { //exists in both
			cr.commonWords.add(el->key, std::min(el->value, item->value));// add common cnt of that word
			commonWordsInFiles += std::min(el->value, item->value);
			if (el->value > item->value) { //we have more of it in smaller subset
				cr.uniqueWords[!firstIsSmaller].add(el->key, el->value - item->value);
			}
			else if (el->value < item->value) {// we have more of it in bigger subset
				cr.uniqueWords[firstIsSmaller].add(el->key, item->value - el->value);
			}
		}
		else {//we dont have it in bigger, its all unique and no common
			cr.uniqueWords[!firstIsSmaller].add(el->key, el->value);
		}
	}

	for (auto el : biggerMSet->umap) { //we have filled common and unique[smaller], we have to fill unique [bigger]
		auto item = cr.commonWords.umap.find(el->key); 
		if (!item) { //doesnt exists in common so we havent searched it and its unique for this one
			cr.uniqueWords[firstIsSmaller].add(el->key, el->value);
		}
	}
	return cr;
}

size_t Comparator::getFile1AllWordsCnt() const
{
	return f1AllWordsCnt;
}

size_t Comparator::getFile2AllWordsCnt() const
{
	return f2AllWordsCnt;
}

size_t Comparator::getCommonForFiles() const
{
	return commonWordsInFiles;
}

