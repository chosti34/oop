#pragma once

enum class Gear
{
    REVERSE = -1,
    NEUTRAL =  0,
    FIRST   =  1,
    SECOND  =  2,
    THIRD   =  3,
    FOURTH  =  4,
    FIFTH   =  5
};

enum class Direction
{
    BACKWARD = -1,
    NONE     =  0,
    FORWARD  =  1
};

class CCar
{
public:
    CCar();
    ~CCar();
    bool IsTurnedOn() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    int GetCurrentSpeed() const;
    std::string GetCurrentDirection() const;
    int GetCurrentGear() const;
private:
    bool m_isTurnedOn;
    Gear m_gear;
    Direction m_direction;
    int m_speed;
};
