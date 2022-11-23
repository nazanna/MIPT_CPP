#include <iostream>
using namespace std;


class SubstepStarter final
{
public:
    int n=0, m=0;
    bool flag=true;
    bool start(){
        // if (flag)
        return flag;
    }
    void end(){
        n++;
        if (n==m)
        flag=true;
        else flag=false;
    }
    bool next_run(){
        m++;
        flag=false;
        bool f=(n>m);
        n=0;
        return (f);
    }
};

void run_substep(SubstepStarter &s) {
        if (s.start()) {
            std::cout << '1';
        }
        s.end();

        std::cout << '#';
    }

void run_step(SubstepStarter &s)
{
    do
    {
        run_substep(s);
        cout <<endl;
    } while (s.next_run());
}

int main()
{
    SubstepStarter s;
    run_step(s);
    return 0;
}