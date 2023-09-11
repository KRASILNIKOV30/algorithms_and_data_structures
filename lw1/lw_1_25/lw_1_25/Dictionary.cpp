#include "Dictionary.h"
#include <algorithm>

void Dictionary::AddSearchWord(std::string const& word)
{
	m_searchWord = word;
	m_searchWordInfo = GetWordInfo(m_searchWord);
}

void Dictionary::AddWord(std::string const& word)
{
	if (IsCompoundedWord(word))
	{
		m_points += word.length();
		m_result.push_back(word);
	}
}

int Dictionary::GetPoints() const
{
	return m_points;
}

std::vector<std::string> Dictionary::GetFoundWords()
{
	std::sort(m_result.begin(), m_result.end(), Compare);
	return m_result;
}

bool Dictionary::Compare(std::string const& left, std::string const& right)
{
	if (left.size() != right.size())
	{
		return left.size() > right.size();
	}

	return left < right;
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

bool Dictionary::IsCompoundedWord(std::string const& word) const
{
	WordInfo wordInfo = GetWordInfo(word);
	bool result = true;
	for (auto it = wordInfo.begin(); it != wordInfo.end() && result; it++)
	{
		result = m_searchWordInfo.contains(it->first) && m_searchWordInfo.at(it->first) >= it->second;
	}

	return result;
}
