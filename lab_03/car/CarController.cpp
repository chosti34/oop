#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

namespace
{
    std::string DirectionToString(const Direction direction)
    {
        std::string directionStr;

        switch (direction)
        {
        case Direction::FORWARD:
        {
            directionStr = "forward";
            break;
        }
        case Direction::BACKWARD:
        {
            directionStr = "backward";
            break;
        }
        case Direction::NONE:
        {
            directionStr = "none";
            break;
        }
        default:
        {
            directionStr = "<unknown direction>";
            break;
        }
        }

        return directionStr;
    }
}

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

    std::cout << "Unknown command!\n";
    return false;
}

bool CCarController::EngineOn(std::istream & /*args*/)
{
    bool callback = m_car.TurnOnEngine();

    if (callback)
    {
        m_output << "Car engine was turned on\n";
    }
    else
    {
        m_output << "Car engine is already turned on\n";
    }

    return callback;
}

bool CCarController::EngineOff(std::istream & /*args*/)
{
    bool callback = m_car.TurnOffEngine();

    if (callback)
    {
        m_output << "Car engine was turned off\n";
    }
    else
    {
        m_output << "Car engine is already turned off\n";
    }

    return callback;
}

bool CCarController::Info(std::istream & /*args*/)
{
    m_output << "Engine: " << ((m_car.IsTurnedOn()) ? "on" : "off") << '\n'
        << "Gear: " << m_car.GetCurrentGear() << '\n'
        << "Speed: " << m_car.GetCurrentSpeed() << '\n'
        << "Direction: " << DirectionToString(m_car.GetCurrentDirection()) << '\n';

    return true;
}

bool CCarController::SetGear(std::istream &args)
{
    int gear;
    args >> gear;

    bool callback = m_car.SetGear(gear);

    if (callback)
    {
        m_output << "Gear was switched on " << m_car.GetCurrentGear() << '\n';
    }
    else
    {
        m_output << "Can't switch gear on " << gear << '\n';
    }

    return callback;
}

bool CCarController::SetSpeed(std::istream &args)
{
    int speed;
    args >> speed;

    bool callback = m_car.SetSpeed(speed);

    if (callback)
    {
        m_output << "Speed was changed on " << m_car.GetCurrentSpeed() << '\n';
    }
    else
    {
        m_output << "Speed is out of range for current gear or car engine is turned off\n";
    }

    return false;
}
