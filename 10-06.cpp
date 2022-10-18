#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
struct Comparator
{
    virtual bool operator()(T const &, T const &) const = 0;
};

template <typename T>
struct Heap
{
    Comparator<T> const &cmp;
    T *memory;
    int n = 0;

    Heap(T *memory, Comparator<T> const &cmp) : memory(memory), cmp(cmp) {}

    void sift_up(const int &u)
    {
        int v = u;
        while (v != 0)
        {
            if ((cmp)(memory[v], memory[(v - 1) / 2]))
            {
                T prom = memory[v];
                memory[v] = memory[(v - 1) / 2];
                memory[(v - 1) / 2] = prom;
                v = (v - 1) / 2;
            }
            else
                break;
        }
    }

    bool is_empty()
    {
        return n == 0;
    }

    void sift_down(const int &num)
    {
        int v = num;

        while (2 * v + 1 <= n - 1)
        {
            int u = 2 * v + 1;
            if (u + 1 <= n - 1 && (cmp)(memory[u + 1], memory[u]))
            {
                u++;
            }
            if ((cmp)(memory[u], memory[v]))
            {
                T prom = memory[v];
                memory[v] = memory[u];
                memory[u] = prom;
                v = u;
            }
            else
                break;
        }
    }

    T get_min()
    {
        return *memory;
    }

    void insert(T x)
    {
        memory[n] = x;
        n++;
        sift_up(n - 1);
    }

    void delete_min()
    {
        if (is_empty())
            cout << "can't delete min";
        else
        {
            memory[0] = memory[n - 1];
            n--;
            sift_down(0);
        }
    }

    void free()
    {
    }
};

struct IntComparator final : Comparator<int>
{
    bool operator()(int const &lha, int const &rha) const override
    {
        return lha < rha;
    }
};

struct CharComparator final : Comparator<char>
{
    bool operator()(char const &lha, char const &rha) const override
    {
        return lha < rha;
    }
};

bool test()
{
    bool t1 = true;
    int *mem = new int[100];
    IntComparator cmp;
    Heap heap(mem, cmp);
    heap.insert(3);
    if (heap.get_min() != 3)
        t1 = false;
    heap.insert(4);
    if (heap.get_min() != 3)
        t1 = false;
    heap.insert(2);
    if (heap.get_min() != 2)
        t1 = false;
    heap.delete_min();
    if (heap.get_min() != 3)
        t1 = false;
    heap.free();

    bool t2 = true;
    char *mems = new char[100];
    CharComparator cmps;
    Heap heaps(mems, cmps);
    heaps.insert('j');
    if (heaps.get_min() != 'j')
        t2 = false;
    heaps.insert('b');
    if (heaps.get_min() != 'b')
        t2 = false;
    heaps.insert('p');
    if (heaps.get_min() != 'b')
        t2 = false;
    heaps.delete_min();
    if (heaps.get_min() != 'j')
        t2 = false;
    heaps.free();
    return t1 * t2;
}

int main()
{

    cout << std::boolalpha << test();
}