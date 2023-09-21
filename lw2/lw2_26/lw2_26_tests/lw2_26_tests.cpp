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

	Input
	(
		"VAR\n"
		"  Ch: CHAR;\n"
		"BEGIN\n"
		"  READ(Ch);\n"
		"  IF Ch <> '#'\n"
		"  THEN\n"
		"    BEGIN\n"
		"      IF Ch <> ' '\n"
		"      THEN\n"
		"        WRITE(Ch);\n"
		"      READ(Ch)\n"
		"    END;\n"
		"  WRITELN\n"
		"END.\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"VAR\n"
		"  Ch: CHAR;\n"
		"BEGIN\n"
		"  READ(Ch);\n"
		"  IF Ch <> '#'\n"
		"  THEN\n"
		"    BEGIN\n"
		"      IF Ch <> ' '\n"
		"      THEN\n"
		"        WRITE(Ch);\n"
		"      ELSE\n"
		"        WRITELN;"
		"      READ(Ch)\n"
		"    END;\n"
		"  WRITELN\n"
		"END.\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"VAR\n"
		"  Rec: RECORD\n"
		"         Name: STRING"
		"         Age: INTEGER"
		"		END;"	
		"BEGIN\n"
		"END\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"Rec: RECORD\n"
		"       Name: STRING\n"
		"       Age: INTEGER\n"
		"	  END;\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"REPEAT\n"
		"  READ(Ch);\n"
		"UNTIL Ch = '#'\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"BEGIN\n"
		"  REPEAT\n"
		"    BEGIN"
		"      IF Ch <> '#'\n"
		"      THEN\n"
		"        WRITE(Ch);\n"
		"      READ(Ch)\n"
		"    END\n"
		"  UNTIL Ch <> '#';\n"
		"END\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"IF Ch <> ' '\n"
		"THEN\n"
		"  READ;\n"
		"ELSE\n"
		"  BEGIN\n"
		"    WRITE;\n"
		"    READ\n"
		"  END\n"
	);
	CHECK(GetOutput() == "Program is correct\n");

	Input
	(
		"BEGIN\n"
		"  IF Ch <> ' '\n"
		"  THEN\n"
		"    Ch := ' ';\n"
		"  IF Ch <> ' '\n"
		"  THEN\n"
		"    Ch := ' '\n"
		"END\n"
	);
	CHECK(GetOutput() == "Program is correct\n");
}

SCENARIO_METHOD(IOFixture, "Incorrect programs")
{	
	Input
	(
		"IF ch <> ' '\n"
		"  BEGIN\n"
		"  END\n"
	);
	CHECK(GetOutput() == "Error at line 2: THEN expected");

	Input
	(
		"IF Ch <> ' '\n"
		"THEN\n"
		"  BEGIN\n"
		"    IF Ch <> ' '\n"
		"    THEN\n"
		"      BEGIN\n"
		"      END\n"
	);
	CHECK(GetOutput() == "Error at line 7: END expected");

	Input
	(
		"REPEAT\n"
		"  BEGIN\n"
		"    WRITE\n"
		"    READ\n"
		"  UNTIL Ch <> ' '\n"
		"END\n"
	);
	CHECK(GetOutput() == "Error at line 5: ");

	Input
	(
		"BEGIN\n"
		"  RECORD\n"
		"  END\n"
		"END\n"
	);
	CHECK(GetOutput() == "Error at line 2: ");

	Input
	(
		"VAR\n"
		"  Ch: CHAR;\n"
		"BEGIN\n"
		"  READ(Ch);\n"
		"  IF Ch <> '#'\n"
		"  THEN\n"
		"    BEGIN\n"
		"      IF Ch <> ' '\n"
		"      THEN\n"
		"        WRITE(Ch);\n"
		"      ELSE\n"
		"        WRITELN;\n"
		"      ELSE\n"
		"        READ(Ch)\n"
		"    END;\n"
		"  WRITELN\n"
		"END.\n"
	);
	CHECK(GetOutput() == "Error at line 13: ");

	Input
	(
		"BEGIN\n"
		"  IF Ch <> ' '\n"
		"  THEN\n"
		"  END\n"
		"END\n"
	);
	CHECK(GetOutput() == "Error at line 5: ");

	Input
	(
		"VAR\n"
		"  Ch: CHAR;\n"
		"END\n"
		"BEGIN\n"
		"END\n"
	);
	CHECK(GetOutput() == "Error at line 3: ");
}