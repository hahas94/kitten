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

#include <csignal>

/**
 * Initialize object.
 * @param num: Some integer in string format. Signed numbers allowed.
 */
BigInteger::BigInteger(const std::string& num)
    {
    if (num.empty()) return;

    int start {0}; // To skip treating sign in the loop below.
    if (num[0] == '-') {
        _is_negative = true;
        start = 1;
    }
    // Ex. num=124579113159 --> digits = [579113159, 124]
    int i {static_cast<int> (num.length())};
    while (i > start) {
        const int pos {std::max(start, i - BASE_LENGTH)};
        _digits.push_back(std::stol(num.substr(pos, i - pos)));
        i -= BASE_LENGTH;
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
    if (_digits.empty()) return "0";

    std::string result;

    if (_is_negative) {
        result += '-';
    }

    // Most significant digit (no padding)
    result += std::to_string(_digits.back());

    // Remaining digits (zero-padded)
    for (int i = static_cast<int> (_digits.size()) - 2; i >= 0; --i) {
        std::string chunk = std::to_string(_digits[i]);
        result += std::string(BASE_LENGTH - chunk.length(), '0') + chunk;
    }

    return result;
}

/**
 * Get the digit at a given position.
 * @return Integer.
 */
uint32_t BigInteger::digit(const std::size_t pos) const {
    if (pos >= _digits.size()) return 0;
    return _digits[pos];
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
    std::vector<uint32_t> result;
    bool result_is_negative;

    if (!_is_negative && !bigint_is_negative) {
        result = _sum(bigint);
        result_is_negative = false;
    } else if (!_is_negative) {
        const bool is_less {this->_signless_less_than(bigint)};
        if (!is_less) {
            result = _diff(bigint);
            result_is_negative = false;
        }
        else {
            result = bigint._diff(*this);
            result_is_negative = true;
        }
    } else if (!bigint_is_negative) {
        const bool is_less {this->_signless_less_than(bigint)};
        if (!is_less) {
            result = _diff(bigint);
            result_is_negative = true;
        }
        else {
            result = bigint._diff(*this);
            result_is_negative = false;
        }
    } else {
        result = _sum(bigint);
        result_is_negative = true;
    }
    
    return {std::move(result), result_is_negative};
}

/**
 * Subtraction between two big ints.
 * @param bigint: Some big integer.
 * @return Difference of this and bigint.
 */
BigInteger BigInteger::operator-(const BigInteger &bigint) const {
    const bool bigint_is_negative {bigint.is_negative()};
    std::vector<uint32_t> result;
    bool result_is_negative;

    if (_is_negative && bigint_is_negative) {
        const bool is_less {this->_signless_less_than(bigint)};
        result = bigint._diff(*this);
        result_is_negative = !is_less;
    } else if (_is_negative) {
        result = _sum(bigint);
        result_is_negative = true;
    } else if (bigint_is_negative) {
        result = _sum(bigint);
        result_is_negative = false;
    } else {
        const bool is_less {this->_signless_less_than(bigint)};
        if (!is_less) {
            result = _diff(bigint);
            result_is_negative = false;
        }
        else {
            result = bigint._diff(*this);
            result_is_negative = true;
        }
    }

    return {std::move(result), result_is_negative};
}

/**
 * Test whether this and a string representation of some integer are equal.
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
    if (size() != bigint.size()) return false;
    if (_is_negative != bigint.is_negative()) return false;

    for (std::size_t i = 0; i < _digits.size(); i++) {
        if (_digits[i] != bigint.digit(i)) return false;
    }
    return true;
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
    int i {static_cast<int> (this->size() - 1)};
    while (i >= 0) {
        if (_digits[i] > bigint.digit(i)) {le = false; break;}
        if (_digits[i] < bigint.digit(i)) {le = true; break;}
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

// Constructor based on digits vector and sign
BigInteger::BigInteger(std::vector<uint32_t>&& digits, bool is_negative) {
    while (digits.size() - 1 > 0 && digits.back() == 0) {
        digits.pop_back();
    }

    if (digits.back() == 0) {
        is_negative = false; // normalize -0 → 0
    }
    _digits = digits;
    _is_negative = is_negative;
}

// Find the sum between this and another bigint, regardless of signs.
std::vector<uint32_t> BigInteger::_sum(const BigInteger &bigint) const {
    const std::size_t max_len {std::max(_digits.size(), bigint.size())};
    std::vector<uint32_t> result;
    result.resize(max_len+1);

    uint32_t carry {0};
    for (std::size_t i {0}; i < max_len || carry > 0; i++) {
        uint32_t sum {carry};
        if (i < _digits.size()) {sum += _digits[i];}
        if (i < bigint.size()) {sum += bigint.digit(i);}
        result[i] = sum % BASE;
        carry = sum / BASE;
    }
    return result;
}

// Find the difference between this and another bigint, regardless of signs.
std::vector<uint32_t> BigInteger::_diff(const BigInteger &bigint) const {
    const std::size_t max_len {std::max(_digits.size(), bigint.size())};

    std::vector<uint32_t> result;
    result.resize(max_len+1);

    int64_t carry {0};
    for (std::size_t i {0}; i < max_len; i++) {
        const int64_t a {i < size() ? _digits[i] - carry : 0 - carry};
        const int64_t b {i < bigint.size() ? bigint.digit(i) : 0};
        int64_t diff {a - b};

        if (diff < 0) {
            diff += BASE;
            carry = 1;
        } else carry = 0;

        result[i] = diff;
    }
    return result;
}

// Whether two big integers are equal in digits.
bool BigInteger::_signless_equals(const BigInteger &bigint) const {
    if (size() != bigint.size()) return false;

    for (std::size_t i = 0; i < _digits.size(); i++) {
        if (_digits[i] != bigint.digit(i)) return false;
    }
    return true;
}

// Whether this is less than some other bigint regardless of their signs.
bool BigInteger::_signless_less_than(const BigInteger& bigint) const {
    const std::size_t a_size = _digits.size();
    const std::size_t b_size = bigint._digits.size();

    if (a_size != b_size) {
        return a_size < b_size;
    }

    // Same length, compare from most significant digit
    for (std::size_t i = a_size; i-- > 0;) {
        if (_digits[i] != bigint._digits[i]) {
            return _digits[i] < bigint._digits[i];
        }
    }

    // Equal
    return false;
}

// ============== END OF FILE ==============
