#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

template<typename T>
class Grid {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    size_type y_size;

protected:
    T *data;
    size_type x_size;
public:
    Grid(size_type y_size, size_type x_size, T const &t) : x_size(x_size), y_size(y_size) {
        data = (T *) operator new(y_size * x_size * sizeof(T));
        for (unsigned i = 0; i < x_size * y_size; ++i) {
            new(data + i) T(t);
        }
    }

    Grid(size_type y_size, size_type x_size) : Grid(y_size, x_size, T()) {}

    //y_size(y_size), x_size(x_size), ata(new T[x_size * y_size]) {}
    Grid(T const &t) : Grid(1, 1, t) {}


    //конструктор копирования
    Grid(Grid<T> const &src) : Grid(src.x_size, src.y_size) {
        for (unsigned i = 0; i < x_size * y_size; ++i) {
            data[i] = src.data[i];
        }
    }

    //оператор копирующего присваивания
    Grid<T> &operator=(Grid<T> const &src) {
        Grid<T> cmp(src);
        std::swap(this->data, cmp.data);
        std::swap(this->x_size, cmp.x_size);
        std::swap(this->y_size, cmp.y_size);
    }

    //конструктор перемещения
    Grid(Grid<T> &&src) : x_size(src.x_size), y_size(src.y_size), data(src.data) {
        src.data = nullptr;
    }

    //перемещающее присваивание
    Grid<T> &operator=(Grid<T> &&src) {
        Grid<T> cmp(std::move(src));
        std::swap(this->data, cmp.data);
        std::swap(this->x_size, cmp.x_size);
        std::swap(this->y_size, cmp.y_size);
    }

    //деструктор
    ~Grid<T>() {
        for (int i = 0; i < x_size * y_size; i++) {
            (*(data + i)).~T();
        }
        operator delete(data);
        //delete[] data;
    }

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T &operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T> &operator=(T const &t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
            *it = t;
        return *this;
    }

    class Arr final {
    private:
        size_type const y_idx;
        Grid const &g;

    public:
        Arr(Grid &g, size_type y_idx) : y_idx(y_idx), g(g) {}

        T &operator[](size_type x_idx) const {
            return g.data[y_idx * g.x_size + x_idx];
        }
    };

    Arr operator[](size_type y_idx) {
        return Arr(*this, y_idx);
    }

    size_type get_y_size() const { return y_size; }

    size_type get_x_size() const { return x_size; }
};


struct Ball {
    sf::CircleShape shape;

    Ball(sf::Color color, int x, int y, int radius) :shape(radius) {
        shape.setFillColor(color);
        shape.setPosition(x, y);
    }

    Ball(Ball const &src) : Ball(src.shape.getFillColor(), src.shape.getPosition().x, src.shape.getPosition().y, src.shape.getRadius()) {
    }

    //оператор копирующего присваивания
    Ball &operator=(Ball const &src) {
        Ball cmp(src);
        std::swap(this->shape, cmp.shape);
    }

    //конструктор перемещения
    Ball(Ball &&src) :shape(src.shape.getRadius()) {
        shape.setFillColor(src.shape.getFillColor());
        shape.setPosition(src.shape.getPosition().x, src.shape.getPosition().y);
    }

    //перемещающее присваивание
    Ball &operator=(Ball &&src) {
        cout << "перемещение"<<endl;
        Ball cmp(std::move(src));
        std::swap(this->shape, cmp.shape);
    }

    ~Ball() {}

    void draw(sf::RenderWindow *window) {
        window->draw(shape);
    }
};

struct Point {

    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    Point(sf::Vector2i vector2) : Point(vector2.x, vector2.y) {}

    Point &operator=(sf::Vector2<int> vec) {
        x = vec.x;
        y = vec.y;
        return *this;
    }
};

struct Field : public Grid<Ball> {
    int size;

    sf::RenderWindow window;
    int size_cell;

    Field(int size, vector<sf::Color> colors) : Grid<Ball>(size, size, Ball(sf::Color::Magenta, 0, 0, 20)),
                                                size(x_size), size_cell(50),
                                                window(sf::VideoMode(600, 400), "") {
        for (unsigned i = 0; i < size * size; ++i) {
            data[i] = Ball(colors[i], size_cell * (i / size), size_cell * (i % size), 20);
        }
    }

    Field() : Field(0, std::vector<sf::Color>()) {}

    void draw() {
        for (unsigned i = 0; i < size * size; ++i) {
            data[i].draw(&window);
        }
    }

    int count(Point point) {
        int x = point.x;
        int y = point.y;
        int number = -1;
        for (unsigned i = 0; i < size * size; ++i) {
            int r = data[i].shape.getRadius();
            if (pow((data[i].shape.getPosition().x + r - x), 2) + pow((data[i].shape.getPosition().y + r - y), 2) <= pow(r, 2)) {
                number = i;
            }
        }
        return number;
    }

    void move(int number, Point start_data, Point start_mouse) {
        if (number >= 0) {
            data[number].shape.setPosition(sf::Mouse::getPosition(window).x + start_data.x - start_mouse.x,
                                           sf::Mouse::getPosition(window).y + start_data.y - start_mouse.y);
        }

    }


    void run() {
        int moving_number = -1;
        Point start_data(0, 0), start_mouse(0, 0);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (event.type == sf::Event::MouseButtonPressed) {
                        start_mouse = sf::Mouse::getPosition(window);
                        moving_number = count(start_mouse);
                        if (moving_number>=0)
                            start_data = Point(data[moving_number].shape.getPosition().x, data[moving_number].shape.getPosition().y);
                    }
                    move(moving_number, start_data, start_mouse);
                }

                if (event.type == sf::Event::MouseButtonReleased) {
                    int number = count(sf::Mouse::getPosition(window));
                    if (moving_number>=0){
                        data[moving_number].shape.setPosition(start_data.x, start_data.y);
                        if (number>=0 && number!=moving_number){
                            std::swap(data[number], data[moving_number]);
                            auto pos = data[number].shape.getPosition();
                            data[number].shape.setPosition(data[moving_number].shape.getPosition());
                            data[moving_number].shape.setPosition(pos);
                        }
                        else{}
                        moving_number = -1;
                    }
                }

            }
            window.clear();
            draw();
            window.display();
        }


    }

};


int main() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    std::vector<sf::Color> color;
    color.push_back(sf::Color::Magenta);
    color.push_back(sf::Color::Blue);
    color.push_back(sf::Color::Green);
    color.push_back(sf::Color::Red);

    std::vector<sf::Color> colors;
    int n=4;
    for (int i=0;i<n*n;i++){
        int k=std::rand()%color.size();
        colors.push_back(color[k]);
    }

    Field field(4, colors);
    field.run();


    return 0;
}
