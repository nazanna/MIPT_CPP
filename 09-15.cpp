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
    unsigned long long x, y;

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

    Point& operator=(Point const &rha){
        x = rha.x;
        y = rha.y;
        return *this;

    }

    void print() const {
        cout << '(' << x << ',' << y << ')' ;
    }
};

struct Rectangle{
    Point point;

    Rectangle (): point(Point(0,0)) {}
    Rectangle (Point const &point): point(point) {}

    Rectangle operator+(Rectangle const &rha) const {
        return Rectangle(Point(point.maxx(rha.point).x, point.maxy(rha.point).y));
    }

    Rectangle operator*(Rectangle const &rha) const {
        return Rectangle(Point(point.minx(rha.point).x, point.miny(rha.point).y));
    }

    Rectangle& operator=(Rectangle const &rha){
        point = rha.point;
        return *this;
    }

    void print () const{
        point.print();
    }
};

Rectangle* R(string str){
    int x, y;
    int num_left, num_comma, num_right;
    num_left = str.find('(');
    num_comma = str.find(',');
    num_right = str.find(')');
    x = stoi(str.substr(num_left+1, num_comma-1));
    y = stoi(str.substr(num_comma+1, num_right-1));
    Point point(x, y);
    cout << x<<"_"<<y<<"_in R";
    Rectangle* rect;
    *rect = Rectangle(point);
    return rect;

}

Rectangle* M(string str){
    Rectangle* rect;
    int num_multi = str.find('*');

    if (num_multi != string::npos){
        string str1 = str.substr(0, num_multi);
        string str2 = str.substr(num_multi+1);
        cout << str1<< '_'<<str2 <<"_in"<< endl;
        *rect = ((*R(str1)) * (*M(str2)));
    }
    else{
        *rect = (*R(str));
    }
    return rect;
}


Rectangle* S(string str){
    //delete waterspaces
    int num_wat = count(str.begin(), str.end(), ' ');
    int len = str.length();
    remove(str.begin(), str.end(), ' ');
    str.resize(len-num_wat);

    Rectangle* rect;
    int num_plus = str.find('+');
    if (num_plus != string::npos){
        string str1 = str.substr(0, num_plus);
        string str2 = str.substr(num_plus+1);
        cout << str1<< '_'<<str2 << endl;
        *rect = Rectangle((*M(str1)) + (*S(str2)).point);
    }
    else{
        *rect = Rectangle((*M(str)).point);
    }
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
    string str="(3,5)";
    rect33 = R(str);
    (*rect33).print();

    return 0;
}