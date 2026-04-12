#include <catch2/catch_test_macros.hpp>
#include "big_integer.hpp"

TEST_CASE("BigInteger: addition") {
    for (long long int i {1234567898765432100}; i < 1234567898765433100; i++) {
        for (long long int j {1234567898765433100}; j < 1234567898765434100; j++) {
            BigInteger n1p {std::to_string(i)};
            BigInteger n2p {std::to_string(j)};
            BigInteger n1n {std::to_string(-i)};
            BigInteger n2n {std::to_string(-j)};

            const BigInteger sum_pp {n1p + n2p};
            REQUIRE(sum_pp.to_string() == std::to_string(i + j));

            const BigInteger sum_nn {n1n + n2n};
            REQUIRE(sum_nn.to_string() == std::to_string(-i + -j));

            const BigInteger sum_pn {n1p + n2n};
            REQUIRE(sum_pn.to_string() == std::to_string(i + -j));

            const BigInteger sum_np {n1n + n2p};
            REQUIRE(sum_np.to_string() == std::to_string(-i + j));
        }
    }
}

TEST_CASE("BigInteger: addition++") {
    BigInteger n0 {"999999999999999999999999"};
    BigInteger n00 {"1"};
    BigInteger s00 {n0 + n00};
    REQUIRE(s00 == "1000000000000000000000000");

    std::string big1(1000, '9'); // "999...999"
    std::string one = "1";
    BigInteger b1 {big1};
    BigInteger b2 {one};
    BigInteger b3 {b1 + b2};

    std::string expected = "1" + std::string(1000, '0');
    REQUIRE(b3 == expected);

    BigInteger n1 {"1234567890123456789012345678901234567891"};
    BigInteger n2 {"2234567890123456789012345678901234567890"};
    BigInteger n3 {n1 + n2};
    REQUIRE (n3 == "3469135780246913578024691357802469135781");

    BigInteger n11 {"1234567890123456789012345678901234567890"};
    BigInteger n33 {n11 + n11 + n11};
    REQUIRE (n33 == "3703703670370370367037037036703703703670");

    BigInteger n22 {"-1234567890123456789012345678901234567890"};
    BigInteger n44 {n22 + n22 + n22};
    REQUIRE (n44 == "-3703703670370370367037037036703703703670");

    BigInteger n55 {"-12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
    BigInteger n66 {"12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
    BigInteger n77 {n55 + n66};
    REQUIRE (n77 == "0");
}

TEST_CASE("BigInteger: subtraction") {
    for (long long int i {1234567898765432100}; i < 1234567898765433100; i++) {
        for (long long int j {1234567898765433100}; j < 1234567898765434100; j++) {
            BigInteger n1p {std::to_string(i)};
            BigInteger n2p {std::to_string(j)};
            BigInteger n1n {std::to_string(-i)};
            BigInteger n2n {std::to_string(-j)};

            const BigInteger sum_pp {n1p - n2p};
            REQUIRE(sum_pp.to_string() == std::to_string(i - j));

            const BigInteger sum_nn {n1n - n2n};
            REQUIRE(sum_nn.to_string() == std::to_string(-i - -j));

            const BigInteger sum_pn {n1p - n2n};
            REQUIRE(sum_pn.to_string() == std::to_string(i - -j));

            const BigInteger sum_np {n1n - n2p};
            REQUIRE(sum_np.to_string() == std::to_string(-i - j));
        }
    }
}

TEST_CASE("BigInteger: subtraction--") {
    BigInteger n01 {"1000000000000000000000000"};
    BigInteger n02 {"1"};
    BigInteger s01 {n01 - n02};
    REQUIRE(s01 == "999999999999999999999999");

    BigInteger n1 {"-1234567890123456789012345678901234567891"};
    BigInteger n2 {"2234567890123456789012345678901234567890"};
    BigInteger n3 {n1 - n2};
    REQUIRE (n3 == "-3469135780246913578024691357802469135781");

    BigInteger n11 {"1234567890123456789012345678901234567890"};
    BigInteger n33 {n11 - n11 - n11};
    REQUIRE (n33 == "-1234567890123456789012345678901234567890");

    BigInteger n22 {"1234567890123456789012345678901234567890"};
    BigInteger n44 {n22 - n22 - n22 - n22 - n22};
    REQUIRE (n44 == "-3703703670370370367037037036703703703670");

    BigInteger n55 {"-12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
    BigInteger n66 {"12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
    BigInteger n77 {n55 - n66};
    REQUIRE (n77 == "-24691357802469135780246913578024691357802469135780246913578024691357802469135780");
}

TEST_CASE("BigInteger: mixture") {
    std::vector<int64_t> test_nums = {
        18446744073709551,
        18446744073709161,
        92233720368547580,
        99233720368477580,
        18440000000000000,
        18000000008880000,
        17000007770000000,
        16000666000000000,
        15055500000000000,
        14044400000000000,
        13000000000000000,
        12000000000002200,
        11000000000110000,
        10000000000000000,
        98765432187654321,
        12345601234567890,
        99999999999999999,
        88888888888888888,
        77777777777777777,
        666666666666666666
    };
    for (auto i : test_nums) {
        for (auto j : test_nums) {
            BigInteger ip {std::to_string(i)};
            BigInteger jp {std::to_string(j)};
            BigInteger in {std::to_string(-i)};
            BigInteger jn {std::to_string(-j)};

            REQUIRE(ip + jp == std::to_string(i + j));
            REQUIRE(ip - jp == std::to_string(i - j));
            REQUIRE(jp - ip == std::to_string(j - i));
            REQUIRE(in + jn == std::to_string(-i + -j));
        }
    }
}

TEST_CASE("BigInteger: order operations") {
    for (long long int i {123456789876543210}; i < 123456789876543310; i++) {
        for (long long int j {123456789876543310}; j < 123456789876543410; j++) {
            BigInteger n1 {std::to_string(i)};
            BigInteger n2 {std::to_string(j)};

            bool eq {n1 == n2};
            REQUIRE(eq == (i == j));

            bool le {n1 < n2};
            REQUIRE(le == (i < j));

            bool leq {n1 <= n2};
            REQUIRE(leq == (i <= j));

            bool ge {n1 > n2};
            REQUIRE(ge == (i > j));

            bool geq {n1 >= n2};
            REQUIRE(geq == (i >= j));

            bool neq {n1 != n2};
            REQUIRE(neq == (i != j));
        }
    }
}