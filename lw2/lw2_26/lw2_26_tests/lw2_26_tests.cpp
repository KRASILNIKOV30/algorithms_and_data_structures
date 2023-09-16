#include "../../../external/catch2/catch.hpp"
#include "../lw2_26/Pascallinter.h"
#include <sstream>

class IOFixture
{
public:

	void Input(std::string input)
	{
		m_inputStream = std::stringstream();
		m_inputStream << input;
	}

	std::string GetOutput()
	{
		m_outputStream = std::stringstream();
		PascalLinter linter(m_inputStream, m_outputStream);
		return m_outputStream.str();
	}

private:
	std::stringstream m_inputStream = std::stringstream();
	std::stringstream m_outputStream = std::stringstream();
};

SCENARIO_METHOD(IOFixture, "Correct programs")
{
	Input
	(
		"IF Ch <> ' '\n"
		"THEN\n"
		"  WRITE(Ch);\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"IF Ch <> ' '\n"
		"THEN\n"
		"  BEGIN\n"
		"    READ(Ch);\n"
		"    WRITE(Ch)\n"
		"  END\n"
	);
	CHECK(GetOutput() == "Program is correct\n");
}

SCENARIO_METHOD(IOFixture, "Incorrect programs")
{
	Input
	(
		"Ch  \n"
		"THEN\n"
		" READ(Ch);\n"
	);
	CHECK(GetOutput() == "Error at line 1: operator expected");
	
	Input
	(
		"IF ch <> ' '\n"
		"  BEGIN\n"
		"  END\n"
	);
	CHECK(GetOutput() == "Error at line 2: THEN expected");
}