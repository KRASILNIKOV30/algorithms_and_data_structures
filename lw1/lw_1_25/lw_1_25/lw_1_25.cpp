//Условие задачи: Задано  некоторое  слово.Требуется  составить из букв
//этого  слова  максимальное  количество  других  слов, которые
//имеются  в  словаре.Каждая  буква  заданного   слова   может
//использоваться  только  один  раз.Например, если в заданном
//слове  имеется 2 буквы 'а', то слова словаря, в которых больше
//двух  букв 'а', не подходят.Каждое найденное слово из словаря
//оценивается  количеством очков, равным  длине слова.Результат
//игры определяется суммой  очков.Первая  строка входного файла
//содержит  заданное  слово.Далее  находятся слова словаря.Все
//слова  состоят   из   строчных(маленьких)  латинских   букв.
//Количество слов словаря  не  превышает 100. В каждом  слове не
//более 20  букв.Длина  заданного  слова  также  не  больше  20
//символов.В первой строке выводится количество набранных очков.
//Начиная со второй строки, следуют найденные слова.Они  должны
//выводиться  по  одному  в  строке по убыванию количества букв.
//Слова  с  одинаковым  количеством  букв  должны  следовать  по
//алфавиту(9).
//Пример
//Ввод         Вывод
//bariton      29
//tara         brant
//triton       tiran
//roba         brat
//tonna        brit
//brat         nota
//nota         roba
//tiran        rab
//brant
//bob
//rab
//brit

//Автор: Красильников Богдан, ПС-21
//Среда выполнения: Visual studio

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

bool CopyStreams(istream& input, ostream& output)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}
	return true;
}

bool OpenStreamsErrorHandling(ifstream& input, ofstream& output)
{

	if (!input.is_open())
	{
		cout << "Failed to open file for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		cout << "Failed to open file for writing\n";
		return false;
	}
	return true;
}

bool SaveErrorHandling(ofstream& output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

bool ProcessArgError(const optional<Args>& args)
{
	if (!args.has_value())
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: copyfile.exe <input file> <output file>\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	ifstream input(args->inputFileName);

	ofstream output(args->outputFileName);

	if (!OpenStreamsErrorHandling(input, output))
	{
		return 1;
	}


	if (!CopyStreams(input, output))
	{
		return 1;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
