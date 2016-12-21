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

    CMyStack(CMyStack<T> &stack)
    {
        CopyFrom(stack.m_top);
    }

    ~CMyStack()
    {
        Clear();
    }

    void Push(const T &data)
    {
        Node *node = new Node;
        node->data = data;

        if (m_top != nullptr)
        {
            node->next = m_top;
        }
        else // stack is empty
        {
            node->next = nullptr;
        }

        m_top = node;
        ++m_size;
    }

    void Pop()
    {
        if (IsEmpty())
        {
            throw std::domain_error("can't pop last element from empty stack");
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
            throw std::domain_error("can't get last element from empty stack");
        }

        return m_top->data;
    }

    bool IsEmpty() const
    {
        return (m_size == 0);
    }

    CMyStack& operator =(CMyStack<T> &stack)
    {
        Clear();
        CopyFrom(stack.m_top);
        stack.Clear();
        return *this;
    }

private:
    void CopyFrom(Node *top)
    {
        if (top->next != nullptr)
        {
            CopyFrom(top->next);
        }

        Push(top->data);
    }

    Node *m_top = nullptr;
    size_t m_size = 0;
};
