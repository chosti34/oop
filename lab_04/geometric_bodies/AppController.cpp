#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "AppController.h"

CAppController::CAppController(std::vector<std::shared_ptr<CBody>> &bodies, std::istream &input, std::ostream &output)
    : m_bodies(bodies)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "CreateSphere", std::bind(&CAppController::CreateSphere, this, std::placeholders::_1) },
        { "CreateParallelepiped", std::bind(&CAppController::CreateParallelepiped, this, std::placeholders::_1) },
        { "CreateCone", std::bind(&CAppController::CreateCone, this, std::placeholders::_1) },
        { "CreateCylinder", std::bind(&CAppController::CreateCylinder, this, std::placeholders::_1) }
    })
{
}

bool CAppController::HandleCommand()
{
    std::string commandLine;

    if (!std::getline(m_input, commandLine) || commandLine.empty())
    {
        return true;
    }

    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        return it->second(strm);
    }

    std::cout << "Unknown command!\n";
    return false;
}

bool CAppController::CreateSphere(std::istream &args)
{
    bool created = false;

    double density;
    double radius;

    if ((args >> density) && (args >> radius))
    {
        std::shared_ptr<CBody> spherePtr(new CSphere(density, radius));
        m_bodies.push_back(spherePtr);
        created = true;
        m_output << "Sphere created!\n";
    }
    else
    {
        m_output << "Can't create this sphere...\n";
    }
    
    return created;
}

bool CAppController::CreateParallelepiped(std::istream &args)
{
    bool created = false;

    double density;
    double width;
    double height;
    double depth;

    if ((args >> density) && (args >> width) && (args >> height) && (args >> depth))
    {
        std::shared_ptr<CBody> parallelepipedPtr(new CParallelepiped(density, width, height, depth));
        m_bodies.push_back(parallelepipedPtr);
        created = true;
        m_output << "Parallelepiped created!\n";
    }
    else
    {
        m_output << "Can't create this parallelepiped...\n";
    }

    return created;
}

bool CAppController::CreateCone(std::istream &args)
{
    bool created = false;

    double density;
    double baseRadius;
    double height;

    if ((args >> density) && (args >> baseRadius) && (args >> height))
    {
        std::shared_ptr<CBody> conePtr(new CCone(density, baseRadius, height));
        m_bodies.push_back(conePtr);
        created = true;
        m_output << "Cone created\n";
    }
    else
    {
        m_output << "Can't create this cone\n";
    }

    return created;
}

bool CAppController::CreateCylinder(std::istream &args)
{
    bool created = false;

    double density;
    double baseRadius;
    double height;

    if ((args >> density) && (args >> baseRadius) && (args >> height))
    {
        std::shared_ptr<CBody> cylinderPtr(new CCylinder(density, baseRadius, height));
        m_bodies.push_back(cylinderPtr);
        created = true;
        m_output << "Cylinder created\n";
    }
    else
    {
        m_output << "Can't create this cylinder\n";
    }

    return created;
}

void CAppController::PrintInfoAboutAllBodies(std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &output)
{
    if (!bodies.empty())
    {
        for (const auto &body : bodies)
        {
            output << body->ToString() << '\n';
        }
    }
}

void CAppController::PrintInfoAboutBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &output)
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

        output << "Body with max mass is " << maxMassBody->ToString() << '\n';
    }
}
