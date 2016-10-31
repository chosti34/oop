#pragma once

enum class Protocol
{
    HTTP = 80,
    HTTPS = 443,
    FTP = 21,
    NONE = 0
};

struct Url
{
    std::string adress;
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
};

Protocol GetProtocol(std::string &str);
int GetDefaultPort(const Protocol &protocol);
bool ParseURL(const std::string &str, Url &url);
void PrintURL(const Url &url);
