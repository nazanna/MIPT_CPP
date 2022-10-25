#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

struct RealFunction
{
    virtual double operator()(unsigned idx) const = 0;
};

struct SimpleFunction: public RealFunction
{
    double operator()(unsigned idx) const override{
        return idx*idx*idx*idx;
    }
};

unsigned max_at(unsigned begin, unsigned end, RealFunction const &f)
{
    double m = f(begin);
    unsigned num = begin;
    for (unsigned i = begin; i != end; i++)
    {
        double y = f(i);
        if (y > m)
        {
            m = y;
            num = i;
        }
    }
    return num;
}

double derivative(unsigned at, RealFunction const &f)
{
    return at*at*at*3;
}

struct DerivativeFunction : public RealFunction
{
    RealFunction const &rf;
    DerivativeFunction(RealFunction const &rf) : rf(rf) {}
    double operator()(unsigned idx) const override
    {
        return derivative(idx, rf);
    }
};

int main()
{
    SimpleFunction f;
    RealFunction const &rf = f;
    DerivativeFunction g(rf);
    std::cout << max_at(1, 1024, g);
    return 0;
}