#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

class Cell final
{
public:
    char v;                                            // Вертикаль, от 'A' до 'H'
    unsigned short int h;                              // Горизонталь, от '1' до '8'
    Cell(char v, unsigned short int h) : v(v), h(h) {} // Конструктор заданной клетки поля с параметрами
    Cell() : Cell('A', 1) {}                           // Конструктор клетки по умолчанию
};

class Piece
{
protected:
    Cell cell;
    Piece(Cell cell) : cell(cell) {}

public:
    virtual bool available(Cell c) const = 0;
};

class King : public Piece
{
public:
    King(Cell cell) : Piece(cell) {}
    bool available(Cell c) const override
    {
        return (abs(cell.v - c.v) <= 1 && abs(cell.h - c.h) <= 1 && !((cell.h==c.h) && (cell.v==c.v)));
    }
};

class Queen : public Piece
{
public:
    Queen(Cell cell) : Piece(cell) {}
    bool available(Cell c) const override
    {
        return (((cell.v == c.v) || (cell.h == c.h) || abs(cell.h - c.h) == abs(cell.v - c.v))&& !((cell.h==c.h) && (cell.v==c.v)));
    }
};

class Rook : public Piece
{
public:
    Rook(Cell cell) : Piece(cell) {}
    bool available(Cell c) const override
    {
        return (((cell.v == c.v) || (cell.h == c.h))&& !((cell.h==c.h) && (cell.v==c.v)));
    }
};
class Bishop : public Piece
{
public:
    Bishop(Cell cell) : Piece(cell) {}
    bool available(Cell c) const override
    {
        return ((abs(cell.h - c.h) == abs(cell.v - c.v))&& !((cell.h==c.h) && (cell.v==c.v)));
    }
};

void are_available(Cell c, const Piece **pieces, bool *availability, std::size_t pieces_count)
{
    for (std::size_t piece_idx = 0; piece_idx != pieces_count; ++piece_idx)
        availability[piece_idx] = pieces[piece_idx]->available(c);
}

int main()
{
    const std::size_t size = 4;
    const Piece *pieces[size];
    bool availability[size];

    pieces[0] = new King(Cell('A', 1));
    pieces[1] = new Queen(Cell('B', 2));
    pieces[2] = new Rook(Cell('C', 3));
    pieces[3] = new Bishop(Cell('D', 4));

    are_available(Cell('A', 1), pieces, availability, size);
    for (auto ans : availability)
        std::cout << ans << ' ';
    std::cout << std::endl;

    for (auto p : pieces)
        delete p;

    return 0;
}
