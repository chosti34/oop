#pragma once

#include <boost/noncopyable.hpp>

class CBody;

class CAppController : boost::noncopyable
{
public:
    CAppController(std::vector<std::shared_ptr<CBody>> &bodies, std::istream &input, std::ostream &output);
    bool HandleCommand();
    
    void PrintInfoAboutAllBodies(std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &output);
    void PrintInfoAboutBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &output);
    void PrintInfoAboutBodyWithMinWeightInWater();

private:
    bool CreateSphere(std::istream &args);
    bool CreateParallelepiped(std::istream &args);
    bool CreateCone(std::istream &args);
    bool CreateCylinder(std::istream &args);

private:
    typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

    std::vector<std::shared_ptr<CBody>> &m_bodies;
    std::istream &m_input;
    std::ostream &m_output;
    const ActionMap m_actionMap;
};
