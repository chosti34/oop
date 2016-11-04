#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

CCarController::CCarController(CCar &car, std::istream &input, std::ostream &output)
    : m_car(car)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "EngineOn", [this](std::istream & strm) {
            return EngineOn(strm);
        } },
        { "EngineOff", bind(&CCarController::EngineOff, this, std::placeholders::_1) },
        { "SetSpeed", bind(&CCarController::SetGear, this, std::placeholders::_1) },
        { "Info", bind(&CCarController::Info, this, std::placeholders::_1) }
    })
{
}

bool CCarController::HandleCommand()
{
    std::string commandLine;
    std::getline(m_input, commandLine);
    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        return it->second(strm);
    }

    return false;
}

bool CCarController::EngineOn(std::istream & /*args*/)
{
    m_car.TurnOnEngine();
    m_output << "Car engine is turned on" << std::endl;
    return true;
}

bool CCarController::EngineOff(std::istream & /*args*/)
{
    if (m_car.TurnOffEngine())
    {
        std::cout << "Car engine is turned off\n";
    }

    return true;
}

bool CCarController::Info(std::istream & /*args*/)
{
    std::string info;

    if (m_car.IsTurnedOn())
    {
        std::cout << "Car engine is on" << std::endl;
    }
    else
    {
        std::cout << "Car engine is off" << std::endl;
    }

    m_output << info;

    return true;
 }

bool CCarController::SetGear(std::istream &args)
{
    int gear;
    args >> gear;
    if (!m_car.SetGear(gear))
    {
        std::string error = "Car engine is turned off or gear doesn't match current car speed\n";
        m_output << error;
    }
    return true;
}

bool CCarController::SetSpeed(std::istream &args)
{
    int speed;
    args >> speed;
    if (!m_car.SetSpeed(speed))
    {
        std::string error = "Speed is out of range for current gear\n";
        m_output << error;
    }
    return true;
}
