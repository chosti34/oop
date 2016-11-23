#include "stdafx.h"
#include "Compound.h"

// сначала плотность равна нулю
CCompound::CCompound() 
    : CBody("Compound", 0) 
{
}

bool CCompound::AddChildBody(const CBody &body)
{
    m_elements.push_back(std::make_shared<CBody>(body));
}

void CCompound::AppendProperties(std::ostream &strm) const
{

}

double CCompound::GetVolume() const
{
    return DBL_EPSILON;
}
