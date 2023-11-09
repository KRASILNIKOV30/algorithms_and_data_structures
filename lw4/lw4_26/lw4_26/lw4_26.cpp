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

#include <algorithm>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <limits>
#include <stack>

using namespace std;
using Graph = std::vector<std::vector<int>>;

struct Cell
{
	int value;
	int parent;
	bool permanent;
	int vertex;
};

struct TableCell
{
	Cell first;
	Cell second;
};

using Table = std::vector<TableCell>;
constexpr int INF = std::numeric_limits<int>::max();

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

void InitGraph(Graph& graph, int const n)
{
	for (int i = 0; i < n; i++)
	{
		graph.emplace_back();
		for (int j = 0; j < n; j++)
		{
			graph[i].emplace_back(0);
		}
	}
}

int ReadGraph(Graph& graph, std::ifstream& input)
{
	int vertexesNum;
	input >> vertexesNum;
	InitGraph(graph, vertexesNum);

	int edgesNum;
	input >> edgesNum;

	for (int i = 0; i < edgesNum; i++)
	{
		int a;
		int b;
		int w;
		input >> a;
		input >> b;
		input >> w;
		graph[a - 1][b - 1] = w;
	}

	return vertexesNum;
}

bool AllPermanent(Table const& table)
{
	for (const auto& cell : table)
	{
		if (!(cell.first.permanent && cell.second.permanent))
		{
			return false;
		}
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

	Graph graph;
	int vertexesNum = ReadGraph(graph, input);

	Table table;

	table.push_back({
		{ 0, 0, true, 0 },
		{INF, 0, false, 0}
		});

	for (int i = 1; i < vertexesNum; i++)
	{
		table.push_back({
			{INF, 0, false, i},
			{INF, 0, false, i}
			}
		);
	}

	int currVertex = 0;
	int isCurrSecond = false;
	while (!AllPermanent(table))
	{
		for (int i = 0; i < vertexesNum; i++)
		{
			TableCell* d = &table[i];
			TableCell* c = &table[currVertex];
			int w = graph[currVertex][i];
			const int currValue = isCurrSecond ? c->second.value : c->first.value;

			if (!d->first.permanent && w != 0 && currValue + w < d->first.value)
			{
				d->second = d->first;
				d->first.value = currValue + w;
				d->first.parent = currVertex;
			}
			else if (!d->second.permanent && w != 0 && currValue + w < d->second.value)
			{
				d->second.value = currValue + w;
				d->second.parent = currVertex;
			}
		}

		Cell* min = new Cell{ INF, 0, false, 0 };
		for (auto& [first, second] : table)
		{
			if (!first.permanent && first.value < min->value)
			{
				min = &first;
				isCurrSecond = false;
			}
			if (!second.permanent && second.value < min->value)
			{
				min = &second;
				isCurrSecond = true;
			}
		}

		if (min->value == INF)
		{
			break;
		}

		min->permanent = true;
		currVertex = min->vertex;
	}

	for (const auto& [first, second] : table)
	{
		int value = 0;
		if (first.vertex == 0)
		{
			continue;
		}
		if (second.value == INF)
		{
			output << "No" << std::endl;
			continue;
		}
		value = second.value;
		output << value << std::endl;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}