#pragma once

class CMyString
{
public:
    CMyString() = default;

    CMyString(const char *pString);
    CMyString(const char *pString, std::size_t length);
    CMyString(const std::string &str);

    CMyString(const CMyString &str); // copy constructor
    CMyString(CMyString &&str); // move constructor

    ~CMyString() noexcept;

    std::size_t GetLength() const;
    const char* GetStringData() const;
    CMyString SubString(std::size_t start, std::size_t length = SIZE_MAX) const;

    void Clear();

    CMyString& operator =(const CMyString &str);
    CMyString& operator =(CMyString &&str);

    CMyString& operator +=(const CMyString &str);

    char& operator [](const std::size_t index);
    const char& operator [](const std::size_t index) const;

private:
    char *m_buffer = nullptr;
    std::size_t m_length = 0;
};

CMyString operator +(const CMyString &lhs, const CMyString &rhs);

bool operator ==(const CMyString &lhs, const CMyString &rhs);
bool operator !=(const CMyString &lhs, const CMyString &rhs);
bool operator <(const CMyString &lhs, const CMyString &rhs);
bool operator >(const CMyString &lhs, const CMyString &rhs);
bool operator >=(const CMyString &lhs, const CMyString &rhs);
bool operator <=(const CMyString &lhs, const CMyString &rhs);

std::istream& operator >>(std::istream &strm, CMyString &str);
std::ostream& operator <<(std::ostream &strm, CMyString &str);
