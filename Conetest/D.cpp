#include <stack>
#include <iostream>


struct DoubleAbstractStack
{
    // some code goes here
public:
    bool push(double next_element)
    {
        // some code goes here
        before_push();
        // push code
        after_push(next_element);
        return true;
    }

    // other public methods
protected:
    virtual void before_push() = 0;
    virtual void after_push(double pushed_element) = 0;
    virtual void before_pop() = 0;
    virtual void after_pop(double popped_element) = 0;
};


struct DoubleStackWithMin : DoubleAbstractStack
{
    std::stack<double> mins;
    DoubleStackWithMin() : DoubleAbstractStack() {}

public:
    void before_push() override{

    }
    void after_push(double pushed_element)override{
        if (mins.size()==0 || pushed_element<mins.top()) mins.push(pushed_element);
    }
    void before_pop() override{

    }
    void after_pop(double popped_element)override{
        if (popped_element == mins.top()) mins.pop();
    }

    double get_min() const
    {
        return mins.top();
    }
};

void operate_stack(DoubleAbstractStack &stack);
void check_min(DoubleStackWithMin const &stack);
int main()
{
    DoubleStackWithMin min_stack;
    operate_stack(min_stack);
    check_min(min_stack);
}