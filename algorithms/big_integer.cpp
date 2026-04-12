/**
 * big_integer.cpp
 * ------------------
 * Description:
 *   Implementation file containing definitions for a Big Integer class.
 *
 *   This object can be used for performing basic arithmetic operations on
 *   integers of arbitrary size.
 *
 *   BigInteger is implemented based on vector representation of the digits
 *   in base 1e9. An instance is created by providing a string representation
 *   of the actual integer. Both positive and negative integers are supported.
 * */

#include "big_integer.hpp"

/**
 * Initialize object.
 * @param num: Some integer in string format. Signed numbers allowed.
 */
BigInteger::BigInteger(const std::string& num)
    {
    _repr = num;
    int start {0}; // To skip treating sign in the loop below.
    if (num[0] == '-') {
        _is_negative = true;
        start = 1;
    }
    // Ex. num=124579113159 --> digits = [579113159, 124]
    int i {static_cast<int> (num.length())};
    while (i > start) {
        const int pos {std::max(start, i - _BASE_LENGTH)};
        _digits.push_back(std::stol(num.substr(pos, i - pos)));
        i -= _BASE_LENGTH;
    }
    }

BigInteger::~BigInteger() = default;

/**
 * Get number of digits.
 * @return n digits.
 */
std::size_t BigInteger::size() const {
    return _digits.size();
}

/**
 * String representation of number.
 * @return number as string.
 */
std::string BigInteger::to_string() const {
    return _repr;
}

/**
 * Get the underlying digits.
 * @return Digit vector.
 */
std::vector<uint32_t> BigInteger::digits() const{
    return _digits;
}

/**
 * Get the sign of the integer. Either positive or negative.
 * @return character sign.
 */
char BigInteger::sign() const {
    return _is_negative ? '-' : '+';
}

/**
 * Whether integer is negative.
 * @return boolean is_negative.
 */
bool BigInteger::is_negative() const {
    return _is_negative;
}

/**
 * Addition between two big ints.
 * @param bigint: Some big integer.
 * @return Sum of this and bigint.
 */
BigInteger BigInteger::operator+(const BigInteger& bigint) const {
    const bool bigint_is_negative {bigint.is_negative()};
    const bool this_is_larger {!(this->_signless_less_than(bigint))};
    std::string result;
    bool result_is_negative;

    if (!_is_negative && !bigint_is_negative) {
        result = _sum(bigint);
        result_is_negative = false;
    } else if (!_is_negative) {
        result = _diff(bigint);
        result_is_negative = !this_is_larger;
    } else if (!bigint_is_negative) {
        result = _diff(bigint);
        result_is_negative = this_is_larger;
    } else {
        result = _sum(bigint);
        result_is_negative = true;
    }

    if (result != "0" && result_is_negative) result = "-" + result;
    return BigInteger(result);
}

/**
 * Subtraction between two big ints.
 * @param bigint: Some big integer.
 * @return Difference of this and bigint.
 */
BigInteger BigInteger::operator-(const BigInteger &bigint) const {
    const bool bigint_is_negative {bigint.is_negative()};
    const bool this_is_larger {!(this->_signless_less_than(bigint))};
    std::string result;
    bool result_is_negative;

    if (_is_negative && bigint_is_negative) {
        result = _diff(bigint);
        result_is_negative = this_is_larger;
    } else if (_is_negative) {
        result = _sum(bigint);
        result_is_negative = true;
    } else if (bigint_is_negative) {
        result = _sum(bigint);
        result_is_negative = false;
    } else {
        result = _diff(bigint);
        result_is_negative = !this_is_larger;
    }

    if (result != "0" && result_is_negative) result = "-" + result;
    return BigInteger(result);
}

/**
 * Test whether this and a string representation of an integer are equal.
 * @param bigint String representation of some integer.
 * @return Equality truthness.
 */
bool BigInteger::operator==(const std::string& bigint) const {
    return to_string() == bigint;
}

/**
 * Test whether this and another big integer are equal.
 * @param bigint Some big integer.
 * @return Equality truthness.
 */
bool BigInteger::operator==(const BigInteger &bigint) const {
    return _digits == bigint.digits() && _is_negative == bigint.is_negative();
}

bool BigInteger::operator<(const BigInteger& bigint) const {
    const bool both_negative {_is_negative && bigint.is_negative()};
    if (!_is_negative && bigint.is_negative()) return false;
    if (_is_negative && !bigint.is_negative()) return true;
    if (this->size() > bigint.size() && both_negative) return true;
    if (this->size() > bigint.size() && !both_negative) return false;
    if (this->size() < bigint.size() && both_negative) return false;
    if (this->size() < bigint.size() && !both_negative) return true;
    if (*this == bigint) return false;

    bool le {false};
    const std::vector<uint32_t> bigint_digits = bigint.digits();
    int i {static_cast<int> (this->size() - 1)};
    while (i >= 0) {
        if (_digits[i] > bigint_digits[i]) {le = false; break;}
        if (_digits[i] < bigint_digits[i]) {le = true; break;}
        i--;
    }
    if (both_negative && !le) return true;
    if (both_negative && le) return false;
    return le;
}

bool BigInteger::operator<=(const BigInteger &bigint) const {
    return *this < bigint || *this == bigint;
}

bool BigInteger::operator>(const BigInteger &bigint) const {
    return !(*this <= bigint);
}

bool BigInteger::operator>=(const BigInteger &bigint) const {
    return !(*this < bigint);
}

bool BigInteger::operator!=(const BigInteger &bigint) const {
    return *this < bigint || *this > bigint;
}

std::ostream& operator<<(std::ostream &os, const BigInteger& bigint) {
    return os << bigint.to_string();
}

// ------------ PRIVATE METHODS ------------

// Find the sum between this and another bigint, regardless of signs.
std::string BigInteger::_sum(const BigInteger &bigint) const {
    const std::vector<uint32_t> bigint_digits = bigint.digits();
    std::string result;
    const std::size_t max_len {std::max(_digits.size(), bigint_digits.size())};

    uint32_t carry {0};
    for (std::size_t i {0}; i < max_len || carry > 0; i++) {
        uint32_t sum {carry};
        if (i < _digits.size()) {sum += _digits[i];}
        if (i < bigint_digits.size()) {sum += bigint_digits[i];}
        const uint32_t remainder = sum % _BASE;
        std::string remainder_str = std::to_string(remainder);
        std::string padding (_BASE_LENGTH - remainder_str.size(), '0');
        result = padding + remainder_str + result;
        carry = sum / _BASE;
    }
    result = remove_leading_zeros(result);
    return result;
}

// Find the difference between this and another bigint, regardless of signs.
std::string BigInteger::_diff(const BigInteger &bigint) const {
    const std::vector<uint32_t> bigint_digits = bigint.digits();
    std::string result;
    const std::size_t max_len {std::max(_digits.size(), bigint_digits.size())};
    const std::vector<uint32_t> a = (this->_signless_less_than(bigint))
        ? bigint_digits : _digits;
    const std::vector<uint32_t> b = (this->_signless_less_than(bigint))
        ? _digits : bigint_digits;

    int64_t carry {0};
    for (std::size_t i {0}; i < max_len; i++) {
        int64_t diff {a[i] - carry};

        if (i < b.size()) {diff -= b[i];}

        if (diff < 0) {
            diff += _BASE;
            carry = 1;
        } else carry = 0;

        std::string remainder_str = std::to_string(diff);
        std::string padding (_BASE_LENGTH - remainder_str.size(), '0');
        result = padding + remainder_str + result;
    }
    result = remove_leading_zeros(result);
    return result;
}

// Whether two big integers are equal in digits.
bool BigInteger::_signless_equals(const BigInteger &bigint) const {
    return _digits == bigint.digits();
}

// Whether this is less than some other bigint regardless of their signs.
bool BigInteger::_signless_less_than(const BigInteger& bigint) const {
    if (this->size() < bigint.size()) return true;
    if (this->size() > bigint.size()) return false;
    if (this->_signless_equals(bigint)) return false;

    const std::vector<uint32_t> bigint_digits = bigint.digits();
    int i {static_cast<int> (this->size() - 1)};
    while (i >= 0) {
        if (_digits[i] > bigint_digits[i]) return false;
        if (_digits[i] < bigint_digits[i]) return true;
        i--;
    }
    return false; // Unreachable
}

// Remove leading zeros from a number.
std::string& BigInteger::remove_leading_zeros(std::string &result) {
    auto nonzero = [](const char s) -> bool {return s != '0';};
    const auto it = std::ranges::find_if(result, nonzero);
    if (it == result.end()) result = "0"; // x - x = "00..0"
    else result = result.substr(std::distance(result.begin(), it), result.size());

    return result;
}

// ============== END OF FILE ==============
