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

class DiscreteState final : public AllState
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

class SegmentState final : public AllState
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

class Cross final : public AllState
{
private:
    AllState *state1, *state2;

public:
    Cross(AllState *state1, AllState *state2) : state1(state1), state2(state2) {}

    bool contains(State s) const override
    {
        return state1->contains(s) && state2->contains(s);
    }
};

class Merge final : public AllState
{
private:
    AllState *state1, *state2;

public:
    Merge(AllState *state1, AllState *state2) : state1(state1), state2(state2) {}

    bool contains(State s) const override
    {
        return state1->contains(s) || state2->contains(s);
    }
};

class Inverse final : public AllState
{
private:
    AllState *state;

public:
    Inverse(AllState *state) : state(state) {}

    bool contains(State s) const override
    {
        return !state->contains(s);
    }
};

/*class AnyState final : public AllState
{
private:
    std::vector<State> points;

public:
    AnyState(std::vector<State> points) : points(points) {}

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
};*/

class ProbabilityTest final
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
    for (unsigned num = 1; num < 100; num += 30)
    {
        f2 << pt.test(s, num, 1) << " , " << pt.test(s, num, 2) << " , " << pt.test(s, num, 3) << " , " << pt.test(s, num, 4) << " , " << num << std::endl;
        f1 << pt.test(d, num, 1) << " , " << pt.test(d, num, 2) << " , " << pt.test(d, num, 3) << " , " << pt.test(d, num, 4) << " , " << num << std::endl;
    }
    f1.close();
    f2.close();
    delete d;
    delete s;

    /*std::fstream f;
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
    delete a;*/

    State E_min = -1000;
    State E_max = 1000;
    ProbabilityTest pt(E_min, E_max);

    std::default_random_engine reng(13);
    std::uniform_int_distribution<int> dstr(E_min, E_max);
    DiscreteState *d1 = new DiscreteState(dstr(reng));
    DiscreteState *d2 = new DiscreteState(dstr(reng));
    Merge *mr = new Merge(d1, d2);
    SegmentState *s = new SegmentState(0, 1);
    std::cout << "test = probability " <<(pt.test(mr, 1000, 1)  + pt.test(mr, 1000, 2))/2<< " , " << 
    (pt.test(s, 1000, 1)  + pt.test(s, 1000, 2))/2 << std::endl;

    delete mr;
    delete d1;
    delete d2;
}

int main()
{
    count();
    DiscreteState *d1 = new DiscreteState(1);
    DiscreteState *d2 = new DiscreteState(0);
    Cross cr(d1, d2);
    std::cout << cr.contains(0) << " " << cr.contains(1) << std::endl;
    Merge mr(d1, d2);
    std::cout << mr.contains(0) << " " << mr.contains(1) << std::endl;
    Inverse in(d1);
    std::cout << in.contains(1) << " " << in.contains(0) << std::endl;
}