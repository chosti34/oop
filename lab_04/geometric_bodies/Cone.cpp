#include "stdafx.h"
#include "Cone.h"

CCone::CCone(double density, double baseRadius, double height)
    : CBody("Cone", density)
    , m_baseRadius(baseRadius)
    , m_height(height)
{
}

double CCone::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCone::GetHeight() const
{
    return m_height;
}

double CCone::GetVolume() const
{
    return M_PI * pow(m_baseRadius, 2) * m_height / 3;
}

void CCone::AppendProperties(std::ostream &strm) const
{
    strm << "\tbase radius = " << GetBaseRadius() << std::endl
         << "\theight = " << GetHeight() << std::endl;
}
