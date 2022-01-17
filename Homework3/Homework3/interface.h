#pragma once
#include <set> //can be used just in words function
#include <string>
#include "Unordered_Map.h"

using std::string;
using std::size_t;

/// Represents a multiset of words
class WordsMultiset {
private:
	Unordered_map<string, size_t> umap;

public:
	friend class Comparator;
	friend class FileComparer;
	//
	/// Can construct U_map with more suitable performance data usage based on the expected words to be added in it
	WordsMultiset(size_t wordCnt=1);
	~WordsMultiset()=default;
	/// Adds times occurences of word to the container
	void add(const std::string& word, size_t times = 1);

	/// Checks whether word is contained in the container
	bool contains(const std::string& word) ;

	/// Number of occurrances of word 
	size_t countOf(const std::string& word) ;

	/// Number of unique words in the container
	size_t countOfUniqueWords() const;

	/// Returns a multiset of all words in the container
	std::multiset<std::string> words() ;

};


class ComparisonReport {
public:
	/// A multiset of all words that exist in both streams
	WordsMultiset commonWords;

	/// Multisets of words unique to the two streams
	/// The first element of the array contains the words that are unique
	/// to the first stream (a) and the second one -- to the second stream (b)
	WordsMultiset uniqueWords[2];
};

/// 
/// Can be used to compare two streams of words
///
class Comparator {
private:
	static const short AVG_WORD_LEN=5;
	size_t f1AllWordsCnt = 0; //keeps the count of all words that have been in file 1 from the last compare call
	size_t f2AllWordsCnt = 0; //keeps the count of all words that have been in file 2 from the last compare call
	size_t commonWordsInFiles = 0;
public:
	Comparator() = default;
	~Comparator() noexcept = default;
	Comparator(const Comparator& other);
	Comparator(Comparator&& other) noexcept;
	Comparator& operator=(const Comparator& other);
	Comparator& operator=(Comparator&& other) noexcept;
	//
	ComparisonReport compare(std::istream& a, std::istream& b);
	size_t getFile1AllWordsCnt() const;
	size_t getFile2AllWordsCnt() const;
	size_t getCommonForFiles() const;
};