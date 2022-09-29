#include <iostream>
#include <random>
#include <fstream>
#include <vector>

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

class AnyState : public AllState
{
private:
    std::vector<State> points;

public:
    AnyState(std::vector<State> points) : points(points){}

    bool contains(State s) const override
    {
        bool contain = false;
        for (int i = 0; i < points.size(); i++)
        {
            if (points[i] == s)
                contain = true;
        }
        return contain;
    }

    AnyState merge(AnyState state1)
    {
        state1.points.insert(state1.points.end(), points.begin(), points.end());
        return state1;
    }

    AnyState cross(AnyState state1)
    {
        std::vector<State> point;
        AnyState state(point);
        for (int i = 0; i < points.size(); i++)
        {
            if (state1.contains(points[i]))
            {
                state.points.push_back(points[i]);
            }
        }
        return state;
    }

    AnyState inverse(AnyState state, State E_min, State E_max)
    {
        std::vector<State> point;
        AnyState statef(point);
        for (State i = E_min; i <= E_max; i++)
        {
            if (!contains(i))
            {
                statef.points.push_back(i);
            }
        }
        return statef;
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

void count()
{
    std::fstream f1, f2;
    f1.open("discrete.txt", std::ios::out);
    f2.open("segment.txt", std::ios::out);
    DiscreteState *d = new DiscreteState(0);
    SegmentState *s = new SegmentState(0, 100);
    State E_min = -1000;
    State E_max = 1000;
    ProbabilityTest pt(E_min, E_max);
    for (unsigned num = 1; num < 100000; num += 30)
    {
        f2 << pt.test(s, num, 1) << " , " << pt.test(s, num, 2) << " , " << pt.test(s, num, 3) << " , " << pt.test(s, num, 4) << " , " << num << std::endl;
        f1 << pt.test(d, num, 1) << " , " << pt.test(d, num, 2) << " , " << pt.test(d, num, 3) << " , " << pt.test(d, num, 4) << " , " << num << std::endl;
    }
    f1.close();
    f2.close();
    delete d;
    delete s;

    std::fstream f;
    f.open("all.csv", std::ios::out);
    std::vector<State> point;
    std::default_random_engine reng(1);
    std::uniform_int_distribution<int> dstr(E_min, E_max);
    for (int i = 0; i < 101; i++)
    {
        point.push_back(dstr(reng));
    }
    AnyState *a = new AnyState(point);
    for (unsigned num = 1; num < 100000; num += 30)
    {
        f << pt.test(a, num, 1) << " , " << pt.test(a, num, 2) << " , " << pt.test(a, num, 3) << " , " << pt.test(a, num, 4) << " , " << num << std::endl;
    }
    f.close();
    delete a;
}

int main()
{
    count();
}