#include "stdafx.h"
#include "url_parse.h"

Protocol GetProtocol(std::string &str)
{
    Protocol protocol;

    boost::algorithm::to_lower(str);

    if (str == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (str == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (str == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else
    {
        protocol = Protocol::NONE;
    }

    return protocol;
}

int GetDefaultPort(const Protocol &protocol)
{
    return static_cast<int>(protocol);
}

bool ParseURL(const std::string &str, Url &url)
{
    const boost::regex urlRegularExpression("^(https?|ftp)://([0-9a-z\.-]+)(:?([0-9]+))?(/(.*))?$", boost::regex_constants::icase);
    boost::smatch matches;

    if (!boost::regex_match(str, matches, urlRegularExpression))
    {
        return false;
    }
    else
    {
        std::string protocol = matches[1].str();
        std::string host = matches[2].str();
        std::string port = matches[4].str();
        std::string document = matches[6].str();

        url.adress = str;
        url.protocol = GetProtocol(protocol);
        url.host = host;
        url.document = document;

        if ((port.empty()) && (port != "0"))
        {
            url.port = GetDefaultPort(url.protocol);
        }
        else
        {
            url.port = stoi(port);
        }

        const int portMinValue = 1;
        const int portMaxValue = 65535;

        if ((url.port < portMinValue) || (url.port > portMaxValue))
        {
            return false;
        }

        return true;
    }
}

void PrintURL(const Url &url)
{
    std::cout << '\n' << url.adress << '\n';

    std::cout << "HOST: " << url.host << '\n';
    std::cout << "PORT: " << url.port << '\n';

    if (url.document.empty())
    {
        std::cout << "DOC: " << "<empty document>" << '\n';
    }
    else
    {
        std::cout << "DOC: " << url.document << '\n';
    }
}
