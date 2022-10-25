#include <cstdint>
#include <iostream>

class Fraction final
{
private:
    // Do NOT rename
    int64_t numerator;
    uint64_t denominator;

    // Do NOT delete
    template <class T>
    friend bool operator==(const Fraction &lhs, const T &rhs)
    {
        return (double)(lhs.numerator / lhs.denominator) == (double)rhs;
    }

public:
    Fraction(int64_t numerator, uint64_t denominator) : numerator(numerator), denominator(denominator) {}
    Fraction() = delete;
    Fraction(const Fraction &rhs) : Fraction(rhs.numerator, rhs.denominator) {}

    Fraction &operator=(const Fraction &rhs)
    {
        Fraction frac(rhs);
        std::swap(this->denominator, frac.denominator);
        std::swap(this->numerator, frac.numerator);
        return *this;
    }

    int64_t gcd(int64_t a, uint64_t b) { return (a == 0 ? b : gcd(b % a, a)); }

    int64_t num()
    {
        return numerator;
    }
    uint64_t den()
    {
        return denominator;
    }

    Fraction operator+(Fraction rha)
    {
        int64_t numer = rha.num() * denominator + numerator * rha.den();
        uint64_t denom = rha.den() * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator+=(Fraction rha)
    {
        *this = (*this)+rha;
        return *this;
    }

    Fraction operator-(Fraction rha)
    {
        int64_t numer = rha.num() * denominator - numerator * rha.den();
        uint64_t denom = rha.den() * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator*(Fraction rha)
    {
        int64_t numer = rha.num() * numerator;
        uint64_t denom = rha.den() * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator-()
    {
        int64_t numer = -1 * numerator;
        Fraction frac(numer, denominator);
        return frac;
    }

    // Your code goes below!
    // Add operators overload here
};

int main()
{
    Fraction a(1,3);
    a += Fraction(2, 3);
    std::cout << (a == 1);
    std::cout << ((Fraction(2, 7) + Fraction(12, 7)) == (int64_t)2) << " ";

    return 0;
}
