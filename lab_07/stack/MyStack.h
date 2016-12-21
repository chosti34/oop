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

    CMyStack(const CMyStack<T> &stack)
    {
        m_top = stack.m_top;
        m_size = stack.m_size;
    }

    ~CMyStack()
    {
        Node *curr = m_top;

        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
            --m_size;
        }

        m_top = nullptr;
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
        Node *curr = m_top;

        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
            --m_size;
        }

        m_top = nullptr;
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

    CMyStack& operator =(const CMyStack<T> &stack)
    {
        Clear();
        m_top = stack.m_top;
        return *this;
    }

private:
    Node *m_top = nullptr;
    size_t m_size = 0;
};
