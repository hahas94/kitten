#include "../../tests/catch.hpp"
#include "reverse_binary.hpp"

TEST_CASE("Test bit_length()"){
  REQUIRE(bit_length(0) == 1);
  REQUIRE(bit_length(1) == 1);
  REQUIRE(bit_length(2) == 2);
  REQUIRE(bit_length(3) == 2);
  REQUIRE(bit_length(4) == 3);
  REQUIRE(bit_length(9) == 4);
  REQUIRE(bit_length(25) == 5);
  REQUIRE(bit_length(111) == 7);
  REQUIRE(bit_length(240) == 8);
  REQUIRE(bit_length(1131) == 11);
  REQUIRE(bit_length(1000000) == 20);
  REQUIRE(bit_length(1000000000) == 30);
}

TEST_CASE("Test to_binary()"){
  REQUIRE(to_binary(0) == "0");
  REQUIRE(to_binary(1) == "1");
  REQUIRE(to_binary(2) == "10");
  REQUIRE(to_binary(3) == "11");
  REQUIRE(to_binary(4) == "100");
  REQUIRE(to_binary(9) == "1001");
  REQUIRE(to_binary(25) == "11001");
  REQUIRE(to_binary(111) == "1101111");
  REQUIRE(to_binary(240) == "11110000");
  REQUIRE(to_binary(1131) == "10001101011");
  REQUIRE(to_binary(1000000) == "11110100001001000000");
}

TEST_CASE("Test to_decimal()"){
  REQUIRE(to_decimal(to_binary(0)) == 0);
  REQUIRE(to_decimal(to_binary(1)) == 1);
  REQUIRE(to_decimal(to_binary(2)) == 2);
  REQUIRE(to_decimal(to_binary(3)) == 3);
  REQUIRE(to_decimal(to_binary(5)) == 5);
  REQUIRE(to_decimal(to_binary(9)) == 9);
  REQUIRE(to_decimal(to_binary(16)) == 16);
  REQUIRE(to_decimal(to_binary(240)) == 240);
  REQUIRE(to_decimal(to_binary(1131)) ==1131);
}
// ============== END OF FILE ==============
