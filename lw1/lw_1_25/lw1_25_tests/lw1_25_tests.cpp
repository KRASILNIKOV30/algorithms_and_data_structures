#include "../../../external/catch2/catch.hpp"
#include "../lw_1_25/Dictionary.h"
#include <iostream>

SCENARIO("Game")
{
	WHEN("Add search word and dictionary")
	{
		Dictionary dict;
		dict.AddSearchWord("hello");
		dict.AddWord("el");

		THEN("Points is equal to zero")
		{
			CHECK(dict.GetPoints() == 0);
			CHECK(dict.GetFoundWords().size() == 1);
			CHECK(dict.GetFoundWords()[0] == "el");
		}
	}

}
