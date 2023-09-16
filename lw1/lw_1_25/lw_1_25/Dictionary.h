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
	std::vector<std::string> GetFoundWords();

private:
	typedef std::vector<char> WordInfo;
	WordInfo GetWordInfo(std::string const& word) const;
	bool IsCompoundedWord(std::string const& word) const;
	static bool Compare(std::string const& left, std::string const& right);

private:
	std::string m_searchWord = "";
	WordInfo m_searchWordInfo = WordInfo();
	std::vector<std::string> m_result{};
	int m_points = 0;
};

