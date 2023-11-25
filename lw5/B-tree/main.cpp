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
#include <stdlib.h> 

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
		tree.Insert(key, inputSize++);
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
	

	while (true)
	{
		system("cls");
		std::cout << tree << std::endl;
		std::cout << "Enter key to find or `e` to exit" << std::endl << "> ";
		int key = 0;
		if (!(std::cin >> key))
		{
			break;
		}
		std::streampos offset;
		try
		{
			offset = tree.Search(key);
		}
		catch (std::invalid_argument)
		{
			std::cout << "Key not found" << std::endl;
			std::cout << "Enter data for " << key << " key" << std::endl << "> ";
			std::string data;
			std::cin >> data;
			output.open(OUTPUT_FILE_NAME, std::ios::binary | std::ios::out);
			output.write(data.c_str(), RECORD_SIZE);
			output.close();
			tree.Insert(key, fileSize++);

			continue;
		}

		output.seekp(offset * RECORD_SIZE);
		char* record = new char[RECORD_SIZE];
		output.open(OUTPUT_FILE_NAME, std::ios::binary | std::ios::in);
		output.read(record, RECORD_SIZE);
		output.close();
		std::cout << record << std::endl;
		delete[] record;

		std::cout << "Continue? (y/n)" << std::endl << "> ";
		std::string answer;
		std::cin >> answer;
		if (answer != "y" && answer != "Y" && answer != "")
		{
			break;
		}
	}

	return 0;
}
