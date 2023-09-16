//26. Программа на ПАСКАЛЕ включает такие  сочетания ключевых
//слов, как    REPEAT..UNTIL, IF..THEN..ELSE, BEGIN..END,
//RECORD..END.Конец оператора  определяется  точкой  с  запятой
//(";").Требуется  проверить  правильность  вложенности данных
//конструкций с учетом допустимости взаимных вложений.В случае
//ошибок указать номер первой некорректной строки(12).
//
//Автор: Красильников Богдан, ПС-21
//Среда выполнения: Visual studio 2022


#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "PascalLinter.h"

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

bool HandleStreams(istream& input, ostream& output)
{
	string str;
	input >> str;
	PascalLinter linter(input, output);

	while (input >> str)
	{
		//dict.AddWord(str);
	}

	//output << dict.GetPoints() << endl;

	/*for (auto& item : dict.GetFoundWords())
	{
		if (!(output << item << endl))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}*/

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
		cout << "Usage: lw2_26.exe <input file> <output file>\n";
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


	if (!HandleStreams(input, output))
	{
		return 1;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
