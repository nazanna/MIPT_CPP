#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

struct Point
{
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y) : x(x), y(y) {}

    Point minx(Point const &rha) const
    {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const
    {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const
    {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const
    {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const
    {
        cout << '(' << x << ',' << y << ')';
    }
};

struct Rectangle
{
    Point point;

    Rectangle() : point(Point(0, 0)) {}
    Rectangle(Point const &point) : point(point) {}

    Rectangle operator+(Rectangle const &rha) const
    {
        return Rectangle(Point(point.maxx(rha.point).x, point.maxy(rha.point).y));
    }

    Rectangle operator*(Rectangle const &rha) const
    {
        return Rectangle(Point(point.minx(rha.point).x, point.miny(rha.point).y));
    }

    void print() const
    {
        point.print();
    }
};

Rectangle *R(string str)
{
    int x, y;
    int num_left, num_comma, num_right;
    num_left = str.find('(');
    num_comma = str.find(',');
    num_right = str.find(')');
    x = stoi(str.substr(num_left + 1, num_comma - 1));
    y = stoi(str.substr(num_comma + 1, num_right - 1));
    Point point(x, y);
    Rectangle *rect = new Rectangle(point);
    return rect;
}

Rectangle *M(string str)
{
    int num_multi = str.find('*');

    if (num_multi != string::npos)
    {
        string str1 = str.substr(0, num_multi);
        string str2 = str.substr(num_multi + 1);
        Rectangle *rect = new Rectangle(((*R(str1)) * (*M(str2))).point);
        return rect;
    }
    Rectangle *rect = new Rectangle((*R(str)).point);
    return rect;
}

Rectangle *S(string str)
{
    // delete waterspaces
    int num_wat = count(str.begin(), str.end(), ' ');
    int len = str.length();
    remove(str.begin(), str.end(), ' ');
    str.resize(len - num_wat);

    int num_plus = str.find('+');
    if (num_plus != string::npos)
    {
        string str1 = str.substr(0, num_plus);
        string str2 = str.substr(num_plus + 1);
        Rectangle *rect = new Rectangle(((*M(str1)) + (*S(str2))).point);
        return rect;
    }
    Rectangle *rect = new Rectangle((*M(str)).point);
    return rect;
}

bool check()
{
    Rectangle *rect = new Rectangle;
    string str = "(5,6) + (7,4)";
    rect = S(str);
    if (!(rect->point.x == 7 && rect->point.y == 6))
    {
        delete rect;
        return false;
    }
    str = "(5,6) * (2,3)";
    rect = S(str);
    if (!(rect->point.x == 2 && rect->point.y == 3))
    {
        delete rect;
        return false;
    }
    str = "(5,6) + (7,4) * (2,3)";
    rect = S(str);
    if (!(rect->point.x == 5 && rect->point.y == 6))
    {
        delete rect;
        return false;
    }
    delete rect;
    return true;
}

int main()
{
    if (check)
        cout << "ok";
    else
        cout << "trouble";
    return 0;
}