#include "stdafx.h"
#include "Car.h"

CCar::CCar()
{
    m_isTurnedOn = false;
    m_speed = 0;
    m_direction = Direction::NONE;
    m_gear = Gear::NEUTRAL;
}

CCar::~CCar() {}

bool CCar::IsTurnedOn() const
{
    return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
    if (!m_isTurnedOn)
    {
        m_isTurnedOn = true;
        return true;
    }

    return false;
}

bool CCar::TurnOffEngine()
{
    if ((m_isTurnedOn) && (m_direction == Direction::NONE) && (m_gear == Gear::NEUTRAL))
    {
        m_isTurnedOn = false;
        return true;
    }

    return false;
}

bool CCar::SetGear(int gear)
{
    if (((!m_isTurnedOn) && (gear != 0)) || (gear < -1) || (gear > 5))
    {
        return false;
    }

    bool switched = false;

    switch (gear)
    {
        case -1:
        {
            if ((m_speed == 0) && ((m_gear == Gear::NEUTRAL) || (m_gear == Gear::FIRST)))
            {
                m_gear = Gear::REVERSE;
                switched = true;
            }
            break;
        }
        case 0:
        {
            m_gear = Gear::NEUTRAL;
            switched = true;
            break;
        }
        case 1:
        {
            if (((m_gear == Gear::REVERSE) && (m_speed == 0)) || 
                ((m_gear == Gear::NEUTRAL) && (m_speed >= 0) && (m_speed <= 30)) ||
                ((m_direction == Direction::FORWARD) && (m_speed >= 0) && (m_speed <= 30)))
            {
                m_gear = Gear::FIRST;
                switched = true;
            }
            break;
        }
        case 2:
        {
            if ((m_speed >= 20) && (m_speed <= 50))
            {
                m_gear = Gear::SECOND;
                switched = true;
            }
            break;
        }
        case 3:
        {
            if ((m_speed >= 30) && (m_speed <= 60))
            {
                m_gear = Gear::THIRD;
                switched = true;
            }
            break;
        }
        case 4:
        {
            if ((m_speed >= 40) && (m_speed <= 90))
            {
                m_gear = Gear::FOURTH;
                switched = true;
            }
            break;
        }
        case 5:
        {
            if ((m_speed >= 50) && (m_speed <= 150))
            {
                m_gear = Gear::FIFTH;
                switched = true;
            }
            break;
        }
    }

    return switched;
}

bool CCar::SetSpeed(int speed)
{
    if (!m_isTurnedOn)
    {
        return false;
    }

    bool changed = false;

    if ((m_gear == Gear::REVERSE) && (speed >= 0) && (speed <= 20))
    {
        m_speed = speed;
        m_direction = (m_speed == 0) ? (Direction::NONE) : (Direction::BACKWARD);
        changed = true;
    }
    else if ((m_gear == Gear::NEUTRAL) && (speed <= m_speed))
    {
        m_speed = speed;
        if (speed == 0)
        {
            m_direction = Direction::NONE;
        }
        changed = true;
    }
    else if (((m_gear == Gear::FIRST) && (speed >= 0) && (speed <= 30)) ||
             ((m_gear == Gear::SECOND) && (speed >= 20) && (speed <= 50)) ||
             ((m_gear == Gear::THIRD) && (speed >= 30) && (speed <= 60)) ||
             ((m_gear == Gear::FOURTH) && (speed >= 40) && (speed <= 90)) ||
             ((m_gear == Gear::FIFTH) && (speed >= 50) && (speed <= 150)))
    {
        m_speed = speed;
        m_direction = Direction::FORWARD;
        changed = true;
    }

    return changed;
}

int CCar::GetCurrentSpeed() const
{
    return m_speed;
}

std::string CCar::GetCurrentDirection() const
{
    std::string direction;

    if (m_direction == Direction::BACKWARD)
    {
        direction = "backward";
    }
    else if (m_direction == Direction::FORWARD)
    {
        direction = "forward";
    }
    else if (m_direction == Direction::NONE)
    {
        direction = "none";
    }

    return direction;
}

int CCar::GetCurrentGear() const
{
    return static_cast<int>(m_gear);
}
