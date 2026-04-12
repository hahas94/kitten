/**
 * big_integer.hpp
 * ------------------
 * Description:
 *   Header file containing declarations for a Big Integer class.
 * */

#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <iostream>
#include <string>
#include <vector>

class BigInteger {
public:
    explicit BigInteger(const std::string& num);
    ~BigInteger();

    std::size_t size() const;
    std::string to_string() const;

    std::vector<uint32_t> digits() const;
    char sign() const;
    bool is_negative() const;

    BigInteger operator+(const BigInteger& bigint) const;
    BigInteger operator-(const BigInteger& bigint) const;
    bool operator==(const std::string& bigint) const;
    bool operator==(const BigInteger& bigint) const;
    bool operator<(const BigInteger& bigint) const;
    bool operator<=(const BigInteger& bigint) const;
    bool operator>(const BigInteger& bigint) const;
    bool operator>=(const BigInteger& bigint) const;
    bool operator!=(const BigInteger& bigint) const;
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigint);

private:
    static constexpr uint32_t _BASE {1000000000}; // class constant value
    static constexpr int _BASE_LENGTH {9};
    bool _is_negative {false};
    std::string _repr {};
    std::vector<uint32_t> _digits {};

    std::string _sum(const BigInteger& bigint) const;
    std::string _diff(const BigInteger& bigint) const;
    bool _signless_equals(const BigInteger& bigint) const;
    bool _signless_less_than(const BigInteger& bigint) const;

    static std::string& remove_leading_zeros(std::string& result);
};

#endif

// ============== END OF FILE ==============

