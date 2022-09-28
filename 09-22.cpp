#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;

using State = int;

class AllState
{
public:
    virtual bool contains(State s) const = 0;
};

class DiscreteState : public AllState
{
private:
    State const s0;

public:
    DiscreteState(State s0) : s0(s0) {}
    bool contains(State s) const override
    {
        return s == s0;
    }
};

class SegmentState : public AllState
{
private:
    State const begin_s0, end_s0;

public:
    SegmentState(State begin_s0, State end_s0) : begin_s0(begin_s0), end_s0(end_s0) {}
    bool contains(State s) const override
    {
        return begin_s0 <= s and end_s0 >= s;
    }
};

class ProbabilityTest
{
private:
    State const E_min, E_max;

public:
    ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) {}

    float test(AllState *system, unsigned test_count, unsigned seed) const
    {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);
        unsigned good = 0;
        State smth;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
        {
            if (system->contains(dstr(reng)))
                ++good;
        }
        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

int main()
{
    DiscreteState *d = new DiscreteState(0);
    SegmentState *s = new SegmentState(0, 100);
    ProbabilityTest pt(-1000, 1000);
    std::cout << pt.test(d, 20000, 2) << std::endl;
    std::cout << pt.test(s, 20000, 1) << std::endl;
    delete d; delete s;
}