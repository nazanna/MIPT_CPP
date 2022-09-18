#include <iostream>
#include<algorithm>
#include <cstdlib>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;


struct Point{
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y):
        x(x), y(y) {}

    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const {
        cout << '(' << x << ',' << y << ')' ;
    }
};

struct Rectangle{
    Point point;

    Rectangle (): point(0,0) {}
    Rectangle (Point const &point): point(point) {}

    Rectangle operator+(Rectangle const &rha) const {
        return Rectangle(Point(point.maxx(rha.point).x, point.maxy(rha.point).y));
    }

    Rectangle operator*(Rectangle const &rha) const {
        return Rectangle(Point(point.minx(rha.point).x, point.miny(rha.point).y));
    }

    void print () const{
        point.print();
    }
};

Rectangle* S(string str){
    remove(str.begin(), str.end(), ' ');
    cout << str << endl;
    Rectangle* rect;
    return rect;


}


int main(){
    Rectangle rect;
    rect.print();
    Point point(2,6);
    Rectangle rect2(point);
    rect2.print();
    Point point2(4,5);
    Rectangle rect3(point2);
    rect3.print();
    (rect3+rect2).print();
    (rect3*rect2).print();
    cout<<endl;
    Rectangle* rect33;
    rect33 = S("ff f");

    return 0;
}