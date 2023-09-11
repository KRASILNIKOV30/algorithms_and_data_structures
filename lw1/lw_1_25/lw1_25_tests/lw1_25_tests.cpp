#include "../../../external/catch2/catch.hpp"
#include "../lw_1_25/Dictionary.h"
#include <iostream>

SCENARIO("Words search")
{
	WHEN("Add search word")
	{
		Dictionary dict;
		dict.AddSearchWord("hello");

		THEN("Points is equal to zero")
		{
			CHECK(dict.GetPoints() == 0);
			CHECK(dict.GetFoundWords().size() == 0);

		}

		AND_WHEN("Add word from search words letter")
		{
			dict.AddWord("holl");

			THEN("This word is found")
			{
				CHECK(dict.GetFoundWords().size() == 1);
				CHECK(dict.GetPoints() == 4);
				auto result = dict.GetFoundWords();
				CHECK(std::equal
				(
					result.begin(),
					result.end(),
					std::vector<std::string>({ "holl" }).begin()
				));
			}

			AND_WHEN("Add word with letters not from search word")
			{
				dict.AddWord("tale");

				THEN("This word is not found")
				{
					CHECK(dict.GetFoundWords().size() == 1);
				}
			}

			AND_WHEN("Add word from search word letters, but in a different qantity")
			{
				dict.AddWord("hohe");

				THEN("This word is not found")
				{
					CHECK(dict.GetFoundWords().size() == 1);
				}
			}
		}
	}
}

SCENARIO("Words sorting")
{
	WHEN("Add search word and dictionary")
	{
		Dictionary dict;
		dict.AddSearchWord("bariton");
		dict.AddWord("tara");
		dict.AddWord("triton");
		dict.AddWord("roba");
		dict.AddWord("tonna");
		dict.AddWord("brat");
		dict.AddWord("nota");
		dict.AddWord("tiran");
		dict.AddWord("brant");
		dict.AddWord("bob");
		dict.AddWord("rab");
		dict.AddWord("brit");	

		THEN("Words is right sorted")
		{
			CHECK(dict.GetPoints() == 29);
			auto result = dict.GetFoundWords();
			CHECK(std::equal
			(
				result.begin(),
				result.end(),
				std::vector<std::string>
				({
					"brant",
					"tiran",
					"brat",
					"brit",
					"nota",
					"roba",
					"rab"
				}).begin()
			));
		}
	}
}
