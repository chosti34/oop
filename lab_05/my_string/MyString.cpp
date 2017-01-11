#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString(const char *pString)
{
    if (pString != nullptr)
    {
        std::size_t length = strlen(pString);
        m_buffer = new char[length + 1];
        memcpy(m_buffer, pString, length + 1);
        m_buffer[length] = '\0';
        m_length = length;
    }
}

CMyString::CMyString(const char *pString, std::size_t length)
{
    if ((pString != nullptr) && (length > 0))
    {
        m_buffer = new char[length + 1];
        memcpy(m_buffer, pString, length);
        m_buffer[length] = '\0';
        m_length = (length > strlen(pString)) ? strlen(pString) : length;
    }
}

CMyString::CMyString(const std::string &str)
{
    std::size_t length = str.length();

    if (length > 0)
    {
        m_buffer = new char[length + 1];
        memcpy(m_buffer, str.c_str(), length + 1);
        m_buffer[length] = '\0';
        m_length = length;
    }
}

CMyString::CMyString(const CMyString &str)
{
    *this = str;
}

CMyString::CMyString(CMyString &&str)
{
    *this = std::move(str);
}

CMyString::~CMyString() noexcept
{
    Clear();
}

const char* CMyString::GetStringData() const
{
    if ((m_buffer != nullptr) && (m_length > 0))
    {
        return m_buffer;
    }

    return "\0";
}

std::size_t CMyString::GetLength() const
{
    return m_length;
}

void CMyString::Clear()
{
    delete [] m_buffer;

    m_buffer = nullptr;
    m_length = 0;
}

CMyString& CMyString::operator =(const CMyString &str)
{
    if (std::addressof(str) != this)
    {
        std::size_t length = str.GetLength();
        char *tmp = new char[length + 1];
        Clear();
        m_buffer = tmp;
        memcpy(m_buffer, str.GetStringData(), length + 1);
        m_length = length;
    }

    return *this;
}

CMyString& CMyString::operator =(CMyString &&str)
{
    if (std::addressof(str) != this)
    {
        std::size_t length = str.GetLength();
        char *tmp = new char[length + 1];
        Clear();
        m_buffer = tmp;
        memmove(m_buffer, str.GetStringData(), length + 1);
        m_length = length;
        str.Clear();
    }

    return *this;
}

CMyString CMyString::SubString(std::size_t start, std::size_t length) const
{
    if (start > m_length)
    {
        return CMyString();
    }

    if (length > m_length)
    {
        length = m_length;
    }

    return CMyString(m_buffer + start, length);
}

CMyString operator +(const CMyString &lhs, const CMyString &rhs)
{
    std::size_t length = lhs.GetLength() + rhs.GetLength();

    char *pString = new char[length + 1];
    memcpy(pString, lhs.GetStringData(), lhs.GetLength());
    memcpy(pString + lhs.GetLength(), rhs.GetStringData(), rhs.GetLength());
    pString[length] = '\0';

    CMyString temp = CMyString(pString, length);
    delete [] pString;

    return temp;
}

CMyString& CMyString::operator +=(const CMyString &rhs)
{
    *this = *this + rhs;
    return *this;
}

bool operator ==(const CMyString &lhs, const CMyString &rhs)
{
    if (lhs.GetLength() != rhs.GetLength())
    {
        return false;
    }

    for (std::size_t i = 0; i < lhs.GetLength(); ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}

bool operator !=(const CMyString &lhs, const CMyString &rhs)
{
    return !(lhs == rhs);
}

bool operator <(const CMyString &lhs, const CMyString &rhs)
{
    std::size_t length = std::min(lhs.GetLength(), rhs.GetLength());

    for (std::size_t i = 0; i < length; ++i)
    {
        if (lhs[i] < rhs[i])
        {
            return true;
        }
        else if (lhs[i] > rhs[i])
        {
            return false;
        }
    }

    return (lhs.GetLength() < rhs.GetLength());
}

bool operator <=(const CMyString &lhs, const CMyString &rhs)
{
    if (lhs == rhs)
    {
        return true;
    }

    return (lhs < rhs);
}

bool operator >=(const CMyString &lhs, const CMyString &rhs)
{
    return !(lhs < rhs);
}

bool operator >(const CMyString &lhs, const CMyString &rhs)
{
    return !(lhs <= rhs);
}

char& CMyString::operator [](const std::size_t index)
{
    if (index >= m_length)
    {
        throw std::out_of_range("index is out of range");
    }

    return m_buffer[index];
}

const char& CMyString::operator [](const std::size_t index) const
{
    if (index >= m_length)
    {
        throw std::out_of_range("index is out of range");
    }

    return m_buffer[index];
}

std::istream& operator >>(std::istream &strm, CMyString &str)
{
    char buffer[256];
    strm.getline(buffer, sizeof(buffer), ' ');
    str = buffer;
    return strm;
}

std::ostream& operator <<(std::ostream &strm, CMyString &str)
{
    strm << str.GetStringData();
    return strm;
}
