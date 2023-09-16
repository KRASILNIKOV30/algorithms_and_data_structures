#include "PascalLinter.h"

PascalLinter::PascalLinter(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	try
	{
		Analyze();
	}
	catch (std::exception e)
	{
		m_output << "Error at line " << m_stringNumber << ": " << e.what();
	}
}

void PascalLinter::Analyze()
{
	std::string word;
	while (NextLine())
	{
		while (m_currentLine >> word)
		{
			if (stack.IsEmpty())
			{
				if (m_keyWords.contains(word))
				{
					stack.Push(word);
				}
				else
				{
					throw std::exception("operator expected");
				}
			}
			else
			{
				if (stack.GetTop() == "IF")
				{
					if (word == "THEN")
					{
						stack.Push(word);
					}
					else if (m_keyWords.contains(word))
					{
						throw std::exception("THEN expected");
					}
				}
			}
		}
	}

	Success();
}

void PascalLinter::Success()
{
	m_output << "Program is correct" << std::endl;
}

void PascalLinter::ExpectOperator()
{

}

bool PascalLinter::NextLine()
{
	std::string line;
	if (getline(m_input, line))
	{
		m_stringNumber++;
		m_currentLine = std::stringstream(line);
		return true;
	}

	return false;
}
