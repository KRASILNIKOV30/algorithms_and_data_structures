#include "Dictionary.h"

void Dictionary::AddSearchWord(std::string const& word)
{
	m_searchWord = word;
	m_searchWordInfo = GetWordInfo(m_searchWord);
}

void Dictionary::AddWord(std::string const& word)
{
	m_words.insert(std::pair<std::string, WordInfo>(word, GetWordInfo(word)));
}

int Dictionary::GetPoints() const
{
	return m_points;
}

std::vector<std::string> Dictionary::GetFoundWords() const
{
	std::vector<std::string> result;
	for (auto& [key, value] : m_words)
	{

	}

	return result;
}

Dictionary::WordInfo Dictionary::GetWordInfo(std::string const& word) const
{
	WordInfo wordInfo;
	for (auto it = word.begin(); it != word.end(); it++)
	{
		wordInfo[*it]++;
	}
	return wordInfo;
}
