//14. Информация  о  файлах  на  жестких  дисках   компьютера
//записана с помощью дерева. Внешнюю память компьютера увеличили
//путем подключения нового жесткого диска. Решено  перенести  на
//него все папки, в которых содержатся только файлы *.cpp вместе
//с папками до корня дерева. Сформировать и показать  на  экране
//получившееся дерево папок (11).
//
//Автор: Красильников Богдан, ПС-21
//Среда выполнения: Visual studio 2022

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "AndOrTree.h"

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
	AndOrTreeHandling(input, output);
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
		cout << "Usage: lw3_27.exe <input file> <output file>\n";
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
