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
	int IFHasOperator = 0;
	while (NextLine())
	{
		while (m_currentLine >> word)
		{
			if (word == "END;" || word == "END.")
			{
				word = "END";
			}

			if (word == "UNTIL")
			{
				if (stack.IsEmpty() || stack.GetTop() != "REPEAT")
				{
					throw std::exception("");
				}
				else
				{
					stack.Pop();
				}
			}

			else if (word == "ELSE")
			{
				if (stack.IsEmpty() || stack.GetTop() != "THEN")
				{
					throw std::exception("");
				}
				else
				{
					stack.Pop();
					stack.Pop();
				}
			}

			else if (word == "RECORD")
			{
				if (!stack.IsEmpty() && stack.GetTop() != "VAR")
				{
					throw std::exception("");
				}
				else
				{
					stack.Push(word);
				}
			}

			else if (stack.IsEmpty())
			{
				if (m_keyWords.contains(word))
				{
					if (word == "END")
					{
						throw std::exception("");
					}
					else
					{
						stack.Push(word);
					}
				}
			}
			else
			{
				if (stack.GetTop() == "VAR" && m_keyWords.contains(word))
				{
					if (word == "BEGIN")
					{
						stack.Pop();
						stack.Push("BEGIN");
					}
					else if (word == "RECORD")
					{
						stack.Push(word);
					}
					else if (word == "END")
					{
						throw std::exception("");
					}
				}

				else if (stack.GetTop() == "IF" && m_keyWords.contains(word))
				{
					if (word == "THEN")
					{
						stack.Push(word);
					}
					else
					{
						throw std::exception("THEN expected");
					}
				}

				else if (stack.GetTop() == "THEN")
				{
					if (m_keyWords.contains(word))
					{
						if (word == "END")
						{
							stack.Pop();
							stack.Pop();

							if (stack.IsEmpty() || stack.GetTop() != "BEGIN")
							{
								throw std::exception("");
							}
							else
							{
								stack.Pop();
							}
						}
						else if (word == "BEGIN" || word == "IF" || word == "REPEAT")
						{
							if (IFHasOperator)
							{
								stack.Pop();
								stack.Pop();
								IFHasOperator = 0;
							}
							stack.Push(word);
						}
						else
						{
							throw std::exception("");
						}
					}
					else
					{
						if (IFHasOperator && m_stringNumber != IFHasOperator)
						{
							stack.Pop();
							stack.Pop();
							IFHasOperator = 0;
						}
						else
						{
							IFHasOperator = m_stringNumber;
						}
					}
				}

				else if (stack.GetTop() == "BEGIN" && m_keyWords.contains(word))
				{
					if (word == "END")
					{
						stack.Pop();

						/*if (!stack.IsEmpty() && stack.GetTop() == "THEN")
						{
							stack.Pop();
							stack.Pop();
						}*/
					}
					else
					{
						stack.Push(word);
					}
				}

				else if (stack.GetTop() == "RECORD" && m_keyWords.contains(word))
				{
					if (word == "END")
					{
						stack.Pop();

						if (!stack.IsEmpty() && stack.GetTop() == "VAR")
						{
							stack.Pop();
						}
					}
					else
					{
						throw std::exception("END excpected");
					}
				}

				else if (stack.GetTop() == "REPEAT" && m_keyWords.contains(word))
				{
					stack.Push(word);
				}
			}
		}
	}

	while (!stack.IsEmpty())
	{
		if (stack.GetTop() == "THEN")
		{
			stack.Pop();
			stack.Pop();
		}
		else if (stack.GetTop() == "BEGIN" || stack.GetTop() == "RECORD")
		{
			throw std::exception("END expected");
		}
		else if (stack.GetTop() == "VAR")
		{
			stack.Pop();
		}
		else if (stack.GetTop() == "END")
		{
			throw std::exception("");
		}
		else if (stack.GetTop() == "REPEAT")
		{
			throw std::exception("UNTIL excpected");
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
