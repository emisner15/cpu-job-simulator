#ifndef JOB_H
#define JOB_H

using namespace std;

class Job
{
private:
    int _cpu;
    int _start_tick;
    int _end_tick;
    int _start_duration;
    int _current_duration;
    string _name;
public:
    void setCPU(int value)
    {
        _cpu = value;
    }
    void setStartTick(int value)
    {
        _start_tick = value;
    }
    void setEndTick(int value)
    {
        _end_tick = value;
    }
    void setStartDuration(int value)
    {
        _start_duration = value;
    }
    void setCurrentDuration(int value)
    {
        _current_duration = value;
    }
    void setName(string value)
    {
        _name = value;
    }
    string getName() const
    {
        return _name;
    }
    int getStartDuration() const
    {
        return _start_duration;
    }
    int getCurrentDuration()
    {
        return _current_duration;
    }
    int getCPU() const
    {
        return _cpu;
    }
    int getStartTick() const
    {
        return _start_tick;
    }
    int getEndTick() const
    {
        return _end_tick;
    }
};

bool operator<(const Job &left, const Job &right)
{
        return left.getStartDuration() < right.getStartDuration();
}

bool operator>(const Job &left, const Job &right)
{
        return left.getStartDuration() > right.getStartDuration();
}

bool operator==(const Job &left, const Job &right)
{
        return left.getStartDuration() == right.getStartDuration();
}




#endif // JOB_H
