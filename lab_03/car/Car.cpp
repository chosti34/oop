#include "stdafx.h"
#include "Car.h"

CCar::CCar()
{
    m_isTurnedOn = false;
    m_speed = 0;
    m_direction = Direction::NONE;
    m_gear = Gear::NEUTRAL;
}

CCar::~CCar()
{
    
}

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
    // если машина не заведена или передана неизвестная передача
    if ((!m_isTurnedOn) || (gear < -1) || (gear > 5))
    {
        return false;
    }

    bool processed = false;

    switch (gear)
    {
        case -1:
        {
            if ((m_speed == 0) && ((m_gear == Gear::NEUTRAL) || (m_gear == Gear::FIRST)))
            {
                m_gear = Gear::REVERSE;
                processed = true;
            }
            break;
        }
        case 0:
        {
            m_gear = Gear::NEUTRAL;
            processed = true;
            break;
        }
        case 1:
        {
            if ( ((m_gear == Gear::REVERSE) && (m_speed == 0)) || 
                 ((m_gear == Gear::NEUTRAL) && (m_speed >= 0) && (m_speed <= 30)) ||
                 ((m_direction == Direction::FORWARD) && (m_speed >= 0) && (m_speed <= 30)) )
            {
                m_gear = Gear::FIRST;
                processed = true;
            }
            break;
        }
        case 2:
        {
            if ((m_speed >= 20) && (m_speed >= 50))
            {
                m_gear = Gear::SECOND;
                processed = true;
            }
            break;
        }
        case 3:
        {
            if ((m_speed >= 30) && (m_speed <= 60))
            {
                m_gear = Gear::THIRD;
                processed = true;
            }
            break;
        }
        case 4:
        {
            if ((m_speed >= 40) && (m_speed <= 90))
            {
                m_gear = Gear::FOURTH;
                processed = true;
            }
            break;
        }
        case 5:
        {
            if ((m_speed >= 50) && (m_speed <= 150))
            {
                m_gear = Gear::FIFTH;
                processed = true;
            }
            break;
        }
    }

    return processed;
}

bool CCar::SetSpeed(int speed)
{
    if (!m_isTurnedOn)
    {
        return false;
    }

    bool processed = false;

    if ((m_gear == Gear::REVERSE) && (speed >= 0) && (speed <= 20))
    {
        m_speed = speed;
        m_direction = (m_speed == 0) ? (Direction::NONE) : (Direction::BACKWARD);
        processed = true;
    }
    else if ((m_gear == Gear::NEUTRAL) && (speed < m_speed))
    {
        m_speed = speed;
        if (speed == 0)
        {
            m_direction = Direction::NONE;
        }
        processed = true;
    }
    else if ( ((m_gear == Gear::FIRST) && (speed >= 0) && (speed <= 30)) ||
              ((m_gear == Gear::SECOND) && (speed >= 20) && (speed <= 50)) ||
              ((m_gear == Gear::THIRD) && (speed >= 30) && (speed <= 60)) ||
              ((m_gear == Gear::FOURTH) && (speed >= 40) && (speed <= 90)) ||
              ((m_gear == Gear::FIFTH) && (speed >= 50) && (speed <= 150)) )
    {
        m_speed = speed;
        m_direction = Direction::FORWARD;
        processed = true;
    }

    return processed;
}

int CCar::GetCurrentSpeed() const
{
    return m_speed;
}

Direction CCar::GetCurrentDirection() const
{
    return m_direction;
}

Gear CCar::GetCurrentGear() const
{
    return m_gear;
}
