#pragma once
#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include "CStringStack.h"

class PascalLinter
{
public:
	PascalLinter(std::istream& input, std::ostream& output);

private:
	void Analyze();
	void Success();
	void ExpectOperator();
	bool NextLine();

private:
	std::istream& m_input;
	std::ostream& m_output;
	std::stringstream m_currentLine;
	int m_stringNumber = 0;
	std::set<std::string> m_keyWords = { "IF", "THEN", "ELSE", "BEGIN", "END", "RECORD", "VAR", "REPEAT", "UNTIL" };
	CStringStack stack;
};

