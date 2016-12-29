#pragma once

template <typename T>
class CMyStack
{
    struct Node
    {
        T data;
        Node *next;
    };

public:
    CMyStack() = default;

    CMyStack(const CMyStack<T> &stack) // copy constructor
    {
        *this = stack;
    }

    CMyStack(CMyStack<T> &&stack) // move constructor
    {
        *this = std::move(stack);
    }

    ~CMyStack() noexcept
    {
        Clear();
    }

    void Push(const T &data)
    {
        Node *node = new Node;
        node->data = data;
        node->next = m_top;
        m_top = node;
        ++m_size;
    }

    void Pop()
    {
        if (IsEmpty())
        {
            throw std::underflow_error("can't pop last element from empty stack");
        }

        Node *node = m_top;
        m_top = m_top->next;
        delete node;
        --m_size;
    }

    void Clear()
    {
        while (!IsEmpty())
        {
            Pop();
        }
    }

    size_t GetSize() const
    {
        return m_size;
    }

    T GetTopElement() const
    {
        if (IsEmpty())
        {
            throw std::underflow_error("can't get last element from empty stack");
        }

        return m_top->data;
    }

    bool IsEmpty() const
    {
        return (m_size == 0);
    }

    const CMyStack& operator =(const CMyStack<T> &stack)
    {
        if (std::addressof(stack) != this)
        {
            CopyItems(stack);
        }

        return *this;
    }

    const CMyStack& operator =(CMyStack &&stack)
    {
        if (std::addressof(stack) != this)
        {
            m_top = stack.m_top;
            m_size = stack.m_size;
            stack.m_top = nullptr;
            stack.m_size = 0;
        }

        return *this;
    }

private:
    void CopyItems(const CMyStack<T> &stack)
    {
        if (!stack.IsEmpty())
        {
            m_top = new Node;
            m_top->data = stack.GetTopElement();

            Node *thisPtr = m_top;
            Node *rhsPtr = stack.m_top->next;

            while (rhsPtr != nullptr)
            {
                thisPtr->next = new Node;
                thisPtr->next->data = rhsPtr->data;
                thisPtr = thisPtr->next;
                rhsPtr = rhsPtr->next;
            }

            m_size = stack.GetSize();
        }
    }

    Node *m_top = nullptr;
    size_t m_size = 0;
};
