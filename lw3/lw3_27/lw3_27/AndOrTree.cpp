#include <iostream>
#include <vector>
#include <string>
#include "AndOrTree.h"

enum class NodeType
{
	AND,
	OR,
	LIST
};

struct Node
{
	std::string value;
	NodeType type;
	int level;
	Node* parent;
	std::vector<Node*> children;
	int childIndex = 0;
};

NodeType GetType(char ch)
{
	switch (ch)
	{
	case 'a':
		return NodeType::AND;
	case 'o':
		return NodeType::OR;
	case 'l':
		return NodeType::LIST;
	default:
		return NodeType::LIST;
	}
}

Node* LoadTree(std::istream& input)
{
	std::string rootValue;
	input >> rootValue;
	char ch;
	input >> ch;
	Node* root = new Node{ rootValue, GetType(ch), 0 };
	Node* parent = root;
	Node* prev = root;

	int curLevel = 1;
	std::string line;
	while (std::getline(input, line))
	{
		std::string levelStr;
		std::string value;
		input >> levelStr;
		int level = levelStr.size();
		input >> value;
		char ch;
		input >> ch;
		Node* newNode = new Node{ value, GetType(ch), level };
		if (level > curLevel)
		{
			parent = prev;
		}
		else if (level < curLevel)
		{
			int dLevel = curLevel - level;
			for (int i = 0; i < dLevel; i++)
			{
				parent = parent->parent;
			}
		}
		curLevel = level;
		newNode->parent = parent;
		parent->children.push_back(newNode);
		prev = newNode;
	}

	return root;
}

void PrintTree(std::ostream& output, Node* node)
{
	for (int i = 0; i < node->level; i++)
	{
		output << '.';
	}
	output << node->value << std::endl;
	switch (node->type)
	{
	case NodeType::AND:
		for (auto& child : node->children)
		{
			PrintTree(output, child);
		}
		break;
	case NodeType::OR:
		PrintTree(output, node->children[node->childIndex]);
		break;
	}
}

void ResetTree(Node* node)
{
	node->childIndex = 0;
	for (auto& child : node->children)
	{
		ResetTree(child);
	}
}

bool NextTree(Node* node, bool& toggled)
{
	if (!toggled)
	{
		switch (node->type)
		{
		case NodeType::AND:
			for (int i = 0; i < node->children.size(); i++)
			{
				node->childIndex = i;
				NextTree(node->children[i], toggled);
			}
			break;
		case NodeType::OR:
			NextTree(node->children[node->childIndex], toggled);
			break;
		}
		if (!toggled && node->type == NodeType::OR && node->childIndex < node->children.size() - 1)
		{
			node->childIndex++;
			toggled = true;
			Node* resetNode = node;
			while (resetNode->parent != nullptr)
			{
				resetNode = resetNode->parent;
				for (int i = resetNode->childIndex - 1; i >= 0; i--)
				{
					ResetTree(resetNode->children[i]);
				}
			} 
		}
	}
	return toggled;
}

void AndOrTreeHandling(std::istream& input, std::ostream& output)
{
	Node* root = LoadTree(input);
	bool toggle = false;
	int i = 1;
	do
	{
		output << i << '.' << std::endl;
		PrintTree(output, root);
		output << std::endl;
		toggle = false;
		i++;
	} while (NextTree(root, toggle));
}