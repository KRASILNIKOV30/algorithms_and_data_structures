//26. Имеется сеть автомобильных дорог. По  некоторым дорогам
//можно  проехать  только  в одном  направлении. Известна  длина
//каждой дороги, причем она может быть разной в  зависимости  от
//направления. Один  из  городов  является  столицей. Требуется
//вывести список длин вторых по минимальности путей из столицы в
//другие города. Допускается присутствие циклических путей(12).
//
//1 - столица
//
//Формат инпута:
//<кол-во вершин> <кол-во ребер>
//<вершина> <вершина> <длина>
//<вершина> <вершина> <длина>
//...
//
//Пример:
//3 2
//1 2 5
//2 3 4
//
//Применить модифицированный алгоритм Дейкстры
//
//Автор: Красильников Богдан, ПС-21
//Среда выполнения: Visual studio 2022

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

optional<Args> ParseArgs(const int argc, char* argv[])
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
	return true;
}

bool OpenStreamsErrorHandling(const ifstream& input, const ofstream& output)
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
		cout << "Usage: lw4_26.exe <input file> <output file>\n";
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
