#include <cstdint>
#include <iostream>

class Fraction final
{
private:
    // Do NOT rename
    int64_t numerator;
    uint64_t denominator;

    // Do NOT delete
    template <typename T>
    friend bool operator==(const Fraction &lhs, const T &rhs)
    {
        return (T)(lhs.numerator / lhs.denominator) == rhs;
        ;
    }

    friend bool operator==(const Fraction &lhs, const Fraction &rhs)
    {
        return (((lhs.numerator == rhs.numerator) && (rhs.denominator == lhs.denominator)) || ((rhs.numerator == lhs.numerator) && (rhs.numerator == 0)));
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
        int64_t gcd_n_d = gcd(rha.denominator, denominator);

        int64_t denom_1 = rha.denominator / gcd_n_d;
        int64_t denom_2 = denominator / gcd_n_d;
        int64_t numer = rha.numerator * denom_2 + numerator * denom_1;
        uint64_t denom = denom_1 * denom_2 * gcd_n_d;
        gcd_n_d = gcd(abs(numer), denom);
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
        int64_t numer = -rha.numerator * denominator + numerator * rha.denominator;
        uint64_t denom = rha.denominator * denominator;
        int64_t gcd_n_d = gcd(abs(numer), denom);
        denom /= gcd_n_d;
        numer = numer / gcd_n_d;
        Fraction frac(numer, denom);
        return frac;
    }

     Fraction operator*(const Fraction &rha) const
    {
        int64_t gcd_n_d_1 = gcd(std::abs(rha.numerator), denominator);
        int64_t gcd_n_d_2 = gcd(std::abs(numerator), rha.denominator);
        int64_t numer = rha.numerator / gcd_n_d_1;
        numer *= (numerator / gcd_n_d_2);
        uint64_t denom = rha.denominator / gcd_n_d_2;
        denom *= (denominator/ gcd_n_d_1);
        Fraction frac(numer, denom);
        return frac;
    }

    Fraction operator-() const
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
    Fraction c(-4, 12);
    Fraction b(2, 6);
    std::cout << (-c + b == Fraction(2,3)) << " ";    
    return 0;
}
