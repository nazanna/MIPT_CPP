#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <cmath>
#include <chrono>
#include <thread>
#include <string>

using namespace std;


struct Ball {
    sf::CircleShape shape;

    Ball(sf::Color color, int x, int y, int radius) : shape(radius) {
        shape.setFillColor(color);
        shape.setPosition(x, y);
    }

    Ball(Ball const &src) : Ball(src.shape.getFillColor(), src.shape.getPosition().x, src.shape.getPosition().y,
                                 src.shape.getRadius()) {
    }

    //оператор копирующего присваивания
    Ball &operator=(Ball const &src) {
        Ball cmp(src);
        std::swap(this->shape, cmp.shape);
    }

    //конструктор перемещения
    Ball(Ball &&src) : shape(src.shape.getRadius()) {
        shape.setFillColor(src.shape.getFillColor());
        shape.setPosition(src.shape.getPosition().x, src.shape.getPosition().y);
    }

    //перемещающее присваивание
    Ball &operator=(Ball &&src) {
        cout << "перемещение" << endl;
        Ball cmp(std::move(src));
        auto color = cmp.shape.getFillColor();
        auto x = cmp.shape.getPosition().x, y = cmp.shape.getPosition().y;
        std::swap(this->shape, cmp.shape);
        shape.setFillColor(color);
        shape.setPosition(x, y);
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

struct Field {
    Ball *data;
    int size, score;
    sf::RenderWindow window;
    sf::Text text;
    sf::Font font;
    int size_cell;

    Field(int size, Ball const &t) : size(size) {
        data = (Ball *) operator new(size * size * sizeof(T));
        for (unsigned i = 0; i < size * size; ++i) {
            new(data + i) Ball(t);
        }
    }

    Grid(int size) : Grid(size, size, T()) {}

    //size(size), size(size), ata(new T[size * size]) {}
    Grid(Ball const &t) : Grid(1, 1, t) {}


    //конструктор копирования
    Grid(Field const &src) : Grid(src.size) {
        for (unsigned i = 0; i < size * size; ++i) {
            data[i] = src.data[i];
        }
    }

    //оператор копирующего присваивания
    Field &operator=(Field const &src) {
        Field cmp(src);
        std::swap(this->data, cmp.data);
        std::swap(this->size, cmp.size);
        std::swap(this->size, cmp.size);
    }

    //конструктор перемещения
    Grid(Field &&src) :
    size(src.size), data(src.data) {
        src.data = nullptr;
    }

    //перемещающее присваивание
    Field &operator=(Field &&src) {
        Field cmp(std::move(src));
        std::swap(this->data, cmp.data);
        std::swap(this->size, cmp.size);
        std::swap(this->size, cmp.size);
    }

    //деструктор
    ~Field() {
        for (int i = 0; i < size * size; i++) {
            (*(data + i)).~Ball();
        }
        operator delete(data);
        //delete[] data;
    }

    Ball operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * size + x_idx];
    }

    Ball &operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * size + x_idx];
    }

    Field &operator=(Ball const &t) {
        for (auto it = data, end = data + size * size; it != end; ++it)
            *it = t;
        return *this;
    }

    class Arr final {
    private:
        size_type const y_idx;
        Grid const &g;

    public:
        Arr(Field &g, size_type y_idx) : y_idx(y_idx), g(g) {}

        Ball &operator[](size_type x_idx) const {
            return g.data[y_idx * g.size + x_idx];
        }
    };

    Arr operator[](size_type y_idx) {
        return Arr(*this, y_idx);
    }

    size_type get_size() const { return size; }

    size_type get_size() const { return size; }

    Field(int size, vector <sf::Color> colors) : Grid<Ball>(size, size, Ball(sf::Color::Magenta, 0, 0, 20)),
                                                 size(size), size_cell(50), score(0), text(),
                                                 window(sf::VideoMode(600, 400), "") {
        for (unsigned i = 0; i < size * size; ++i) {
            data[i] = Ball(colors[i], size_cell * (i / size), size_cell * (i % size), 20);
        }
        font.loadFromFile("../arial.ttf");
        text.setFont(font);
        text.setPosition(window.getSize().x * 0.8, 0);
        text.setString(sf::String("Score: \n" + std::to_string(score)));
        text.setFillColor(sf::Color::Red);
        text.setOutlineColor(sf::Color::Red);
    }

    Field() : Field(0, std::vector<sf::Color>()) {}

    //оператор копирующего присваивания
    Field &operator=(Field const &src) {
        Field cmp(src);
        std::swap(this->size, cmp.size);
        std::swap(this->score, cmp.score);
        std::swap(this->window, cmp.window);
        std::swap(this->text, cmp.text);
        std::swap(this->font, cmp.font);
        std::swap(this->size_cell, cmp.size_cell);
        std::swap(this->data, cmp.data);
        std::swap(this->size, cmp.size);
        std::swap(this->size, cmp.size);
    }

    //конструктор перемещения
    Field(Field &&src) : size(src.size), size(src.size), data(src.data), {
        src.data = nullptr;

    }

    //перемещающее присваивание
    Field &operator=(Field &&src) {
        cout << "перемещение" << endl;
        Field cmp(std::move(src));
        auto color = cmp.shape.getFillColor();
        auto x = cmp.shape.getPosition().x, y = cmp.shape.getPosition().y;
        std::swap(this->shape, cmp.shape);
        shape.setFillColor(color);
        shape.setPosition(x, y);
    }

    ~Field() {}

    void draw() {
        for (unsigned i = 0; i < size * size; ++i) {
            data[i].draw(&window);
        }
        window.draw(text);
    }

    vector<int> check() {
        vector<int> poses;
        for (int i = 0; i < size; i++) {
            int start = 0, max = 1, current = 1;
            if (poses.size() == 0) {
                for (int j = 1; j < size; j++) {
                    auto color1 = data[i * size + j - 1].shape.getFillColor();
                    auto color2 = data[i * size + j].shape.getFillColor();
                    if (color1 == color2) {
                        current++;
                    } else {
                        if (current > max) {
                            max = current;
                            start = j - current;
                        }
                        current = 1;
                    }
                }
                if (current > max) {
                    max = current;
                    start = size - current;
                }
                if (max >= 3) {
                    for (int j = 0; j < max; j++) {
                        poses.push_back(i * size + start + j);
                    }
                }
            }
        }

        if (poses.size() == 0) {
            for (int j = 0; j < size; j++) {
                int start = 0, max = 1, current = 1;
                if (poses.size() == 0) {
                    for (int i = 1; i < size; i++) {
                        auto color1 = data[(i - 1) * size + j].shape.getFillColor();
                        auto color2 = data[i * size + j].shape.getFillColor();
                        if (color1 == color2) {
                            current++;
                        } else {
                            if (current > max) {
                                max = current;
                                start = i - current;
                            }
                            current = 1;
                        }
                    }
                    if (current > max) {
                        max = current;
                        start = size - current;
                    }
                    if (max >= 3) {
                        for (int i = 0; i < max; i++) {
                            poses.push_back(i * size + start * size + j);
                        }
                    }
                }
            }
        }
        return poses;
    }

    void remove(vector<int> poses) {
        score += poses.size();
        text.setString("Score: \n" + std::to_string(score));
        if (abs(poses[0] - poses[1]) > 1) {
            for (int i = 0; i < poses.size(); i++) {
                int k = poses[i] / size;
                for (int j = poses[i] % size; j > 0; j--) {
                    data[k * size + j].shape.setFillColor(data[k * size + j - 1].shape.getFillColor());
                    data[k * size + j].shape.setRadius(data[k * size + j - 1].shape.getRadius());
                }
                int random = std::rand() % (size * size);
                data[k * size].shape.setFillColor(data[random].shape.getFillColor());
                data[k * size].shape.setRadius(data[random].shape.getRadius());
            }
        } else {
            int m = *std::max_element(poses.begin(), poses.end());
            int k = m / size;
            cout << m << " " << k * size + poses.size() << endl;
            for (int j = m; j >= k * size + poses.size(); j--) {
                data[j].shape.setFillColor(data[j - poses.size()].shape.getFillColor());
                data[j].shape.setRadius(data[j - poses.size()].shape.getRadius());
            }
            for (int j = k * size; j < k * size + poses.size(); j++) {
                int random = std::rand() % (size * size);
                data[j].shape.setFillColor(data[random].shape.getFillColor());
                data[j].shape.setRadius(data[random].shape.getRadius());
            }
        }
    }

    int count(Point point, int ban_number = -1) {
        int x = point.x;
        int y = point.y;
        int number = -1;
        for (unsigned i = 0; i < size * size; ++i) {
            if (i != ban_number) {
                int r = data[i].shape.getRadius();
//                cout << x << " " << y << " " << data[i].shape.getPosition().x << " "
//                     << data[i].shape.getPosition().y << " " << data[i].shape.getRadius() << " " << i << endl;
                if (pow((data[i].shape.getPosition().x + r - x), 2) + pow((data[i].shape.getPosition().y + r - y), 2)
                    <= pow(r, 2)) {
                    number = i;
                }
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

    void mouse_released(int moving_number, Point start_data) {
        int number = count(sf::Mouse::getPosition(window), moving_number);
        if (moving_number >= 0) {
            data[moving_number].shape.setPosition(start_data.x, start_data.y);
            bool near1 = ((moving_number % size == number % size) && (abs(moving_number / size - number / size) == 1));
            bool near2 = ((moving_number / size == number / size) && (abs(moving_number % size - number % size) == 1));
            bool near = near1 xor near2;
            if (number >= 0 && number != moving_number && near) {

                auto color = data[number].shape.getFillColor();
                data[number].shape.setFillColor(data[moving_number].shape.getFillColor());
                data[moving_number].shape.setFillColor(color);

                auto radius = data[number].shape.getRadius();
                data[number].shape.setRadius(data[moving_number].shape.getRadius());
                data[moving_number].shape.setRadius(radius);

            }
            moving_number = -1;
        }
    }

    void full_draw(int moving_number) {
        window.clear();
        draw();
        if (moving_number >= 0) {
            data[moving_number].draw(&window);
        }
        window.display();

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
                        if (moving_number >= 0)
                            start_data = Point(data[moving_number].shape.getPosition().x,
                                               data[moving_number].shape.getPosition().y);
                    }
                    move(moving_number, start_data, start_mouse);
                }

                if (event.type == sf::Event::MouseButtonReleased) {
                    mouse_released(moving_number, start_data);
                }

            }
            vector<int> f = check();
            if (f.size() > 0) {
                full_draw(moving_number);
                remove(f);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            full_draw(moving_number);
        }


    }

};


int main() {
    std::vector <sf::Color> color;
    color.push_back(sf::Color::Magenta);
    color.push_back(sf::Color::Blue);
    color.push_back(sf::Color::Green);
    color.push_back(sf::Color::Red);

    std::vector <sf::Color> colors;
    int n = 6;
    for (int i = 0; i < n * n; i++) {
        int k = std::rand() % color.size();
        colors.push_back(color[k]);
    }

    Field field(n, colors);
    field.run();

    return 0;
}
