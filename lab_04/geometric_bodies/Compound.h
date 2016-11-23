#pragma once

#include "Body.h"

class CCompound final : public CBody
{
public:
    CCompound();

    bool AddChildBody(const CBody &body);
    double GetVolume() const;

protected:
    void AppendProperties(std::ostream &strm) const;

private:
    std::vector<std::shared_ptr<CBody>> m_elements;

};
