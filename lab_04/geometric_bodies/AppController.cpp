#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Compound.h"
#include "AppController.h"

CAppController::CAppController(std::vector<std::shared_ptr<CBody>> &bodies, std::istream &input, std::ostream &output)
    : m_bodies(bodies)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "CreateSphere", std::bind(&CAppController::CreateSphere, this, std::placeholders::_1) },
        { "CreateParallelepiped", std::bind(&CAppController::CreateParallelepiped, this, std::placeholders::_1) },
        { "CreateCone", std::bind(&CAppController::CreateCone, this, std::placeholders::_1) },
        { "CreateCylinder", std::bind(&CAppController::CreateCylinder, this, std::placeholders::_1) },
        { "CreateCompound", std::bind(&CAppController::CreateCompound, this, std::placeholders::_1) }
    })
{
}

bool CAppController::HandleCommand()
{
    std::string commandLine;

    if ((!std::getline(m_input, commandLine)) || (commandLine.empty()))
    {
        return false;
    }

    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    bool handled = false;
    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        it->second(strm);
        handled = true;
    }
    else
    {
        std::cout << "Unknown command!\n";
    }

    return handled;
}

bool CAppController::CreateSphere(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 2)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CSphere>(parametrs.at(0), parametrs.at(1));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Sphere created!\n";
    }
    else
    {
        m_output << "Can't create this sphere...\n"
                 << "Usage: CreateSphere <density> <radius>\n";
    }
    
    return created;
}

bool CAppController::CreateParallelepiped(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 4)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CParallelepiped>(parametrs.at(0), parametrs.at(1), parametrs.at(2), parametrs.at(3));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Parallelepiped created!\n";
    }
    else
    {
        m_output << "Can't create this parallelepiped...\n"
                 << "Usage: CreateParallelepiped <density> <width> <height> <depth>\n";
    }

    return created;
}

bool CAppController::CreateCone(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 3)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CCone>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Cone created\n";
    }
    else
    {
        m_output << "Can't create this cone\n"
                 << "Usage: CreateCone <density> <base radius> <height>\n";
    }

    return created;
}

bool CAppController::CreateCylinder(std::istream &args)
{
    bool created = false;

    CCylinder cylinder(1, 2, 3);

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 3)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CCylinder>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Cylinder created\n";
    }
    else
    {
        m_output << "Can't create this cylinder\n"
                 << "Usage: CreateCylinder <density> <base radius> <height>\n";
    }

    return created;
}

bool CAppController::CreateCompound(std::istream &args)
{
    std::string str;

    CCompound compoundBody();

    while (std::getline(std::cin, str))
    {
        // 1) Сформировать CBody
        // 2) Запушить в вектор
    }

    return true;
}

void CAppController::PrintInfoAboutAllBodies(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    if (!bodies.empty())
    {
        for (const auto &body : bodies)
        {
            strm << body->ToString() << '\n';
        }
    }
}

void CAppController::PrintInfoAboutBodyWithMaxMass(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    if (!bodies.empty())
    {
        std::shared_ptr<CBody> maxMassBody = bodies.at(0);

        for (const auto &body : bodies)
        {
            if (body->GetMass() > maxMassBody->GetMass())
            {
                maxMassBody = body;
            }
        }

        strm << "Body with max mass is " << maxMassBody->ToString() << '\n';
    }
}

void CAppController::PrintInfoAboutBodyWithMinWeightInWater(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    const double waterDensity = 1000;

    if (!bodies.empty())
    {
        std::shared_ptr<CBody> minDensityBody = bodies.at(0);
        double minWeightInWater = GetBodyWeightInWater(*minDensityBody);

        if (minWeightInWater < 0)
        {
            minWeightInWater = 0;
        }

        for (const auto &body : bodies)
        {
            if (abs(GetBodyWeightInWater(*body)) < minWeightInWater)
            {
                minWeightInWater = GetBodyWeightInWater(*body);
                minDensityBody = body;
            }
        }

        strm << "Body with min weight in water is " << minDensityBody->ToString() << '\n'
             << "\tWeight in water: " << minWeightInWater << '\n';
    }
}

double CAppController::GetBodyWeightInWater(const CBody &body) const
{
    const double gravityAcceleration = 9.8;
    const double waterDensity = 1000;

    return (body.GetDensity() - waterDensity) * gravityAcceleration * body.GetVolume();
}
