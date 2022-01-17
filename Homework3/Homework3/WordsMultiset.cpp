#include "interface.h"

WordsMultiset::WordsMultiset(size_t wordCnt)
	:umap(wordCnt)
{
}

void WordsMultiset::add(const std::string& word, size_t times)
{
	auto el = umap.find(word);
	if (el) { //exists
		el->value += times;
	}
	else {
		umap.insert(word, times);
	}
}

bool WordsMultiset::contains(const std::string& word) 
{
	return umap.contains(word);
}

size_t WordsMultiset::countOf(const std::string& word) 
{
	auto el = umap.find(word);
	return (el !=nullptr ? el->value : 0);
}

size_t WordsMultiset::countOfUniqueWords() const
{
	return umap.get_size();
}

std::multiset<std::string> WordsMultiset::words() 
{
	std::multiset <string> mset;
	for (auto el : umap) {
		for (size_t i = 0; i < el->value; i++) {
			mset.insert(el->key);
		}
	}
	return mset;
}