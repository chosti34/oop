#pragma once

class CBody
{
public:
    CBody(const std::string &type, double density);
    virtual ~CBody();

    double GetDensity() const;
    double GetMass() const;
    virtual double GetVolume() const = 0;

    std::string ToString() const;

protected:
    virtual void AppendProperties(std::ostream &strm) const = 0;

private:
    double m_density;
    std::string m_type;
};
