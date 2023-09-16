#pragma once
#include <string>

struct StackNode
{
	std::string value;
	StackNode* next;
};

class CStringStack
{
public:
	CStringStack() = default;
	bool IsEmpty() const;
	std::string& GetTop() const;
	void Push(std::string value);
	void Pop();
	int GetSize() const;
	~CStringStack();
	CStringStack(CStringStack const& source);
	CStringStack(CStringStack&& other) noexcept;
	CStringStack& operator=(CStringStack const& other);
	CStringStack& operator=(CStringStack&& other) noexcept;

private:
	void Clear();

private:
	StackNode* m_top = nullptr;
	//добавить размер (исправлено)
	int m_size = 0;
};

