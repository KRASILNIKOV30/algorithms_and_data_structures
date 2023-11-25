//27. Имеется  И - ИЛИ   дерево, соответствующее   некоторому
//множеству  конструкций.Требуется выдать на экран в наглядном
//виде все элементы дерева(14).
//
//Автор: Красильников Богдан, ПС-21
//Среда выполнения: Visual studio 2022

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "Tree.h"

const std::string OUTPUT_FILE_NAME = "out.bin";
const std::streamsize RECORD_SIZE = 20;

std::streamsize FillTree(std::istream& input, std::ostream& output, Tree& tree)
{
	std::streamsize inputSize = 0;
	while (true)
	{
		int key;
		std::string data;
		if (!(input >> key >> data))
		{
			break;
		}

		output.write(data.c_str(), RECORD_SIZE);
		tree.Insert(key, inputSize);
		++inputSize;
	}

	return inputSize;
}

bool OpenStreamsErrorHandling(std::ifstream& input)
{

	if (!input.is_open())
	{
		std::cout << "Failed to open file for reading\n";
		return false;
	}

	return true;
}

bool SaveErrorHandling(std::fstream& output)
{
	if (!output.flush())
	{
		std::cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	std::cout << "Enter input file name" << std::endl;
	std::cout << "> ";
	std::string inputFileName;
	std::cin >> inputFileName;

	std::ifstream input(inputFileName);
	std::fstream output(OUTPUT_FILE_NAME, std::ios::binary | std::ios::out);

	if (!OpenStreamsErrorHandling(input))
	{
		return 1;
	}

	Tree tree;
	std::streamsize fileSize = FillTree(input, output, tree);
	output.close();
	output.open(OUTPUT_FILE_NAME, std::ios::binary | std::ios::in);
	
	std::cout << tree;

	/*for (int i = fileSize - 1; i >= 0; i--)
	{
		output.seekp(i * RECORD_SIZE);
		char* record = new char [RECORD_SIZE];
		output.read(record, RECORD_SIZE);
		std::cout << record << std::endl;
	}*/

	return 0;
}
