#include "CStringStack.h"
#include <stdexcept>

bool CStringStack::IsEmpty() const
{
    return m_top == nullptr;
}

std::string& CStringStack::GetTop() const
{
    if (IsEmpty())
    {
        throw std::logic_error("Stack is empty");
    }

    return m_top->value;
}

void CStringStack::Push(std::string value)
{
    //утечка пам€ти (при присваивании строки) (»справлено)
    StackNode* top = new StackNode{value, m_top};
    m_top = top;
    m_size++;
}

void CStringStack::Pop()
{
    if (IsEmpty())
    {
        throw std::logic_error("Stack is empty");
    }
    StackNode* top = m_top;
    m_top = m_top->next;
    delete top;
    m_size--;
}

int CStringStack::GetSize() const
{
    return m_size;
}

void CStringStack::Clear()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

CStringStack::~CStringStack()
{
    Clear();
}

CStringStack::CStringStack(CStringStack const& source)
{
    auto sourcesNode = source.m_top;
    m_top = new StackNode{ sourcesNode->value, nullptr };
    m_size++;
    auto prev = m_top;
    while (sourcesNode->next != nullptr)
    {
        sourcesNode = sourcesNode->next;
        try
        {
            prev->next = new StackNode{ sourcesNode->value, nullptr };
        }
        catch (std::exception)
        {
            Clear();
            throw;
        }
        m_size++;
        prev = prev->next;
    }
}

CStringStack::CStringStack(CStringStack&& other) noexcept
    : m_top(other.m_top)
    , m_size(other.m_size)
{
    other.m_top = nullptr;
    other.m_size = 0;
}

CStringStack& CStringStack::operator=(CStringStack const& other)
{
    if (&other != this)
    {
        *this = std::move(CStringStack(other));
    }
    return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
    if (&other != this)
    {
        m_top = other.m_top;
        m_size = other.m_size;
        other.m_top = nullptr;
        other.m_size = 0;
    }
    return *this;
}
