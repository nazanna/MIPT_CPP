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
        return (T)(lhs.numerator / lhs.denominator) == (T)rhs;
    }

    friend bool operator==(const Fraction &lhs, const Fraction &rhs)
    {
        return (((lhs.numerator == rhs.numerator) && (rhs.denominator == lhs.denominator)) || ((rhs.numerator == lhs.numerator) && (rhs.numerator == 0)));
    }

    friend bool operator==(const Fraction &lhs, const int64_t &rhs)
    {
        return (((lhs.numerator == rhs) && (1 == lhs.denominator)) || ((lhs.numerator == 0) && (rhs == 0)));
    }

public:
    Fraction(int64_t numerator_out, uint64_t denominator_out) : numerator(numerator_out / gcd(abs(numerator_out), denominator_out)),
                                                                denominator(denominator_out / gcd(abs(numerator_out), denominator_out)) {}
    Fraction() = delete;
    Fraction(const Fraction &rhs) : Fraction(rhs.numerator, rhs.denominator) {}

    Fraction &operator=(const Fraction &rhs)
    {
        Fraction frac(rhs);
        std::swap(this->denominator, frac.denominator);
        std::swap(this->numerator, frac.numerator);
        return *this;
    }

    int64_t gcd(int64_t a, int64_t b) const { return (a == 0 ? b : gcd(b % a, a)); }

    Fraction operator+(const Fraction &rha) const
    {
        int64_t numer = rha.numerator * denominator + numerator * rha.denominator;
        uint64_t denom = rha.denominator * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction &operator+=(const Fraction &rha) 
    {
        *this = (*this) + rha;
        return *this;
    }

    Fraction operator-(const Fraction &rha) const
    {
        int64_t numer = rha.numerator * denominator - numerator * rha.denominator;
        uint64_t denom = rha.denominator * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator*(const Fraction &rha) const
    {
        int64_t numer = rha.numerator * numerator;
        uint64_t denom = rha.denominator * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator-()const
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
    Fraction a(1, 3);
    a += Fraction(2, 3);
    std::cout << (a == 1);
    std::cout << ((Fraction(2, 7) * Fraction(12, 7)) == Fraction(24, 49)) << " ";

    return 0;
}
