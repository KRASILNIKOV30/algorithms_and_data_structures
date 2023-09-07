#pragma once
#include <string>
#include <map>
#include <vector>

class Dictionary
{
public:
	Dictionary() = default;
	void AddSearchWord(std::string const& word);
	void AddWord(std::string const& word);
	int GetPoints() const;
	std::vector<std::string> GetFoundWords() const;

private:
	typedef std::map<char, int> WordInfo;
	WordInfo GetWordInfo(std::string const& word) const;
	std::map<std::string, WordInfo> m_words = std::map<std::string, WordInfo>();
	std::string m_searchWord = "";
	WordInfo m_searchWordInfo = WordInfo();
	int m_points = 0;
};

