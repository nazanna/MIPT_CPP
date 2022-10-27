#include <iostream>
#include <cstdlib>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    size_type y_size, x_size;
    T *data;

public:
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(new T[x_size * y_size]) {}
    Grid(T const &t) : Grid(1, 1)
    {
        data[0] = t;
    }
    Grid(size_type y_size, size_type x_size, T const &t) : Grid(y_size, x_size)
    {
        for (unsigned i = 0; i < x_size * y_size; ++i)
        {
            data[i] = t;
        }
    }

    //конструктор копирования
    Grid(Grid<T> const &src) : Grid(src.x_size, src.y_size)
    {
        for (unsigned i = 0; i < x_size * y_size; ++i)
        {
            data[i] = src.data[i];
        }
    }

    //оператор копирующего присваивания
    Grid<T> &operator=(Grid<T> const &src)
    {
        Grid<T> cmp(src);
        std::swap(this->data, cmp.data);
        std::swap(this->x_size, cmp.x_size);
        std::swap(this->y_size, cmp.y_size);
    }

    //конструктор перемещения
    Grid(Grid<T> &&src) : x_size(src.x_size), y_size(src.y_size), data(src.data)
    {
        src.data = nullptr;
    }

    //перемещающее присваивание
    Grid<T> &operator=(Grid<T> &&src)
    {
        Grid<T> cmp(std::move(src));
        std::swap(this->data, cmp.data);
        std::swap(this->x_size, cmp.x_size);
        std::swap(this->y_size, cmp.y_size);
    }

    //деструктор
    ~Grid<T>()
    {
        delete[] data;
    }

    T operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T &operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T> &operator=(T const &t)
    {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it)
            *it = t;
        return *this;
    }

    class Arr final
    {
    private:
        size_type const y_idx;
        Grid const &g;

    public:
        Arr(Grid &g, size_type y_idx) : y_idx(y_idx), g(g) {}

        T &operator[](size_type x_idx) const
        {
            return g.data[y_idx * g.x_size + x_idx];
        }
    };

    Arr operator[](size_type y_idx)
    {
        return Arr(*this, y_idx);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};
/*
template <typename T, unsigned n>
class Grid_n final
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    size_type n_size;
    Grid_n<T, n - 1> *grid;

public:
    template <typename... Args>
    Grid_n(size_type n_size, Args... sizes) : n_size(n_size), grid(new Grid_n<T, n - 1>(sizes...)) {}

    template <typename... Args>
    Grid_n(size_type n_size, Args... sizes, T const &t) : Grid_n(n_size, sizes...)
    {
        if (sizeof...(sizes) == 0)
            for (unsigned i = 0; i < n_size; ++i)
            {
                grid[0] = t;
            }
    }

    template <typename... Args>
    T* operator()(size_type n_index, Args... indexes) const
        {
            return (grid+n_size*n_index+grid(indexes...));
        }
    
        //конструктор копирования
        Grid(Grid<T> const &src) : Grid(src.x_size, src.y_size)
        {
            for (unsigned i = 0; i < x_size * y_size; ++i)
            {
                data[i] = src.data[i];
            }
        }

        //оператор копирующего присваивания
        Grid<T> &operator=(Grid<T> const &src)
        {
            Grid<T> cmp(src);
            std::swap(this->data, cmp.data);
            std::swap(this->x_size, cmp.x_size);
            std::swap(this->y_size, cmp.y_size);
        }

        //конструктор перемещения
        Grid(Grid<T> &&src) : x_size(src.x_size), y_size(src.y_size), data(src.data)
        {
            src.data = nullptr;
        }

        //перемещающее присваивание
        Grid<T> &operator=(Grid<T> &&src)
        {
            Grid<T> cmp(std::move(src));
            std::swap(this->data, cmp.data);
            std::swap(this->x_size, cmp.x_size);
            std::swap(this->y_size, cmp.y_size);
        }

        //деструктор
        ~Grid<T>()
        {
            delete[] data;
        }

        T operator()(size_type y_idx, size_type x_idx) const
        {
            return data[y_idx * x_size + x_idx];
        }

        T &operator()(size_type y_idx, size_type x_idx)
        {
            return data[y_idx * x_size + x_idx];
        }

        Grid<T> &operator=(T const &t)
        {
            for (auto it = data, end = data + x_size * y_size; it != end; ++it)
                *it = t;
            return *this;
        }

        class Arr final{
            private:
            size_type const y_idx;
            Grid const &g;
            public:
            Arr(Grid &g, size_type y_idx): y_idx(y_idx), g(g) {}

            T& operator[](size_type x_idx) const {
                return g.data[y_idx*g.x_size+x_idx];
            }
        };

        Arr operator[](size_type y_idx)
        {
            return Arr(*this, y_idx);
        }

        size_type get_y_size() const { return y_size; }
        size_type get_x_size() const { return x_size; }
};*/

int main()
{

    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());
    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    return 0;
}