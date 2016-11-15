#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder(double density, double baseRadius, double height)
    : CBody("Cylinder", density)
    , m_baseRadius(baseRadius)
    , m_height(height)
{
}

double CCylinder::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCylinder::GetHeight() const
{
    return m_height;
}

double CCylinder::GetVolume() const
{
    return M_PI * pow(m_baseRadius, 2) * m_height;
}

void CCylinder::AppendProperties(std::ostream &strm) const
{
    strm << "\tbase radius = " << GetBaseRadius() << std::endl
         << "\theight = " << GetHeight() << std::endl;
}
