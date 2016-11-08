#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

CCarController::CCarController(CCar &car, std::istream &input, std::ostream &output)
    : m_car(car)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "EngineOn", bind(&CCarController::EngineOn, this, std::placeholders::_1) },
        { "EngineOff", bind(&CCarController::EngineOff, this, std::placeholders::_1) },
        { "SetGear", bind(&CCarController::SetGear, this, std::placeholders::_1) },
        { "SetSpeed", bind(&CCarController::SetSpeed, this, std::placeholders::_1) },
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
    if (m_car.TurnOnEngine())
    {
        m_output << "Car engine is turned on\n";
        return true;
    }

    return false;
}

bool CCarController::EngineOff(std::istream & /*args*/)
{
    if (m_car.TurnOffEngine())
    {
        m_output << "Car engine is turned off\n";
        return true;
    }

    return false;
}

bool CCarController::Info(std::istream & /*args*/)
{
    std::string info;

    if (m_car.IsTurnedOn())
    {
        info = "Car engine is on\nGear: " + std::to_string(m_car.GetCurrentGear()) +
               "\nSpeed: " + std::to_string(m_car.GetCurrentSpeed()) +
               "\nDirection: " + m_car.GetCurrentDirection() + '\n';
    }
    else
    {
        info = "Car engine is off\n";
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
        std::string alert = "Gear doesn't match current car speed or car engine is turned off\n";
        m_output << alert;
    }
    else
    {
        std::string msg = "Gear was switched on " + std::to_string(gear) + '\n';
        m_output << msg;
    }

    return true;
}

bool CCarController::SetSpeed(std::istream &args)
{
    int speed;
    args >> speed;

    if (!m_car.SetSpeed(speed))
    {
        std::string alert = "Speed is out of range for current gear or car engine is turned off\n";
        m_output << alert;
    }

    return true;
}
