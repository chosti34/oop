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
        CopyItems(stack.m_top);
    }

    CMyStack(CMyStack<T> &&stack) // move constructor
    {
        m_top = stack.m_top;
        m_size = stack.m_size;
        stack.m_top = nullptr;
        stack.m_size = 0;
    }

    ~CMyStack() noexcept
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

    CMyStack& operator =(const CMyStack<T> &stack)
    {
        if (std::addressof(stack) != this)
        {
            CopyItems(stack.m_top);
        }
        return *this;
    }

    CMyStack& operator =(CMyStack &&stack)
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

    void Print(std::ostream &strm = std::cout) const
    {
       Node *curr = m_top;

       while (curr != nullptr)
       {
           strm << curr->data;
           curr = curr->next;
       }
    }

private:
    void CopyItems(Node *top)
    {
        if (top->next != nullptr)
        {
            CopyItems(top->next);
        }

        Push(top->data);
    }

    Node *m_top = nullptr;
    size_t m_size = 0;
};
