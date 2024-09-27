#include "../../tests/catch.hpp"
#include "interval_cover.hpp"

TEST_CASE("Example 1") {
  std::istringstream iss {"-0.5 1\n3\n-0.9 -0.1\n-0.2 2\n-0.7 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n2 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 2") {
  std::istringstream iss {"0 1\n3\n0 0.25\n0.25 0.75\n0.75 0.999\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 3") {
  std::istringstream iss {"0 1\n3\n0 0.25\n0.25 0.75\n0.75 1\n1 1\n1\n1 1"};
  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"3\n2 1 0 \n1\n0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 4") {
  std::istringstream iss {"0 1\n5\n0 0.25\n0.20 0.50\n0.25 0.75\n0.25 0.76\n0.75 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"3\n4 3 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 5") {
  std::istringstream iss {"0 1\n5\n0.1 0.25\n0.20 0.50\n0.25 0.75\n0.25 0.76\n0.75 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 6") {
  std::istringstream iss {"0 1\n5\n0 0.25\n0.20 0.50\n0.25 0.75\n0.25 0.76\n0.77 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 7") {
  std::istringstream iss {"0 3\n3\n0 2\n3 5\n7 10\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 8") {
  std::istringstream iss {"0 5\n5\n0 5\n0 7\n2 10\n5 10\n7 12\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 9") {
  std::istringstream iss {"0 10\n4\n0 4\n3 7\n8 10\n9 12\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 10") {
  std::istringstream iss {"0 10\n6\n0 3\n2 5\n4 6\n5 9\n8 10\n9 11\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"4\n4 3 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 11") {
  std::istringstream iss {"0 10\n4\n0 2\n2 5\n5 8\n8 10\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"4\n3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 12") {
  std::istringstream iss {"0 5\n4\n0 0\n1 2\n3 3\n4 5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 13") {
  std::istringstream iss {"0 10\n7\n0 3\n2 5\n4 7\n6 9\n8 10\n3 4\n0 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"5\n4 3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 14") {
  std::istringstream iss {"0 10\n5\n0 1\n1 2\n0 9\n3 5\n8 10\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n4 2 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 15") {
  std::istringstream iss {"0 10\n5\n-5 -1\n-2 3\n2 6\n4 10\n9 12\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"3\n3 2 1 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 16") {
  std::istringstream iss {"0 10\n1\n-1.5 10.5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 17") {
  std::istringstream iss {"-1.5 10.32\n4\n-1.5 2.0\n2.1 5.5\n5.5 7.0\n7.5 10.5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 18") {
  std::istringstream iss {"-2.5 10.32\n5\n-2.5 1.0\n-1.0 4.5\n3.5 8.5\n8.0 10.5\n9.5 12.0\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"4\n3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 19") {
  std::istringstream iss {"-1.0 10.4\n6\n-1.0 0.5\n0.5 2.0\n2.0 3.5\n3.5 6.0\n5.5 8.0\n7.5 10.5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"6\n5 4 3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 20") {
  std::istringstream iss {"-5.0 4\n4\n-5.0 -2.5\n-4.5 -1.0\n-3.0 0.0\n-2.0 2.0\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 21") {
  std::istringstream iss {"-5.5 10.5\n4\n-5.5 -1.5\n-1.5 0.0\n0.0 3.5\n3.5 10.5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"4\n3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 22") {
  std::istringstream iss {"-0.5 10.5\n8\n-0.5 0.1\n0.05 0.5\n0.5 1.0\n1.0 1.5\n1.5 2.0\n2.0 2.5\n2.5 3.0\n3.0 10.5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"8\n7 6 5 4 3 2 1 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 23") {
  std::istringstream iss {"0 5\n2\n1 2\n2 5\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 24") {
  std::istringstream iss {"0 1\n1\n0 0.50000\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 25") {
  std::istringstream iss {"0 1\n1\n0.49000 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 26") {
  std::istringstream iss {"0 1\n1\n0.000001 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 27") {
  std::istringstream iss {"0 1\n1\n0 0.999999\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 28") {
  std::istringstream iss {"0 0.999999\n1\n0 0.99999\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 29") {
  std::istringstream iss {"0 1\n1\n-1 0\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 30") {
  std::istringstream iss {"0 1\n2\n1 2\n3 4\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 31") {
  std::istringstream iss {"0 2\n3\n0 0\n0 1\n0 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n2 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 32") {
  std::istringstream iss {"0 2\n3\n0 0\n0 1\n1 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 33") {
  std::istringstream iss {"0 2\n3\n1 1\n1 2\n2 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"impossible\n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 34") {
  std::istringstream iss {"0 2\n3\n0 1\n1 1\n1 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n2 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 35") {
  std::istringstream iss {"0 2\n4\n0 0\n0 1\n1 1\n1 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n3 1 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 36") {
  std::istringstream iss {"0 2\n4\n0 1\n1 1\n1 2\n2 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n2 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 37") {
  std::istringstream iss {"0 2\n4\n0 0\n0 1\n0 2\n1 1\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n2 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 38") {
  std::istringstream iss {"0 2\n4\n0 0\n0 2\n1 1\n2 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n1 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 39") {
  std::istringstream iss {"0 2\n5\n0 0\n0 1\n0 2\n1 1\n1 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"1\n2 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 40") {
  std::istringstream iss {"0 2\n5\n0 1\n1 1\n1 2\n0 0\n2 2\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n2 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 41") {
  std::istringstream iss {"-3 -1\n5\n0 1\n-1 -1\n-2 -1\n-4 -2\n-1 3\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"2\n2 3 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 42") {
  std::istringstream iss {"0 10\n8\n0 3\n1 4\n2 5\n3 6\n4 7\n5 8\n6 9\n7 10\n"};

  std::ostringstream oss {};

  // // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  solve();
  
  std::string output {"4\n7 6 3 0 \n"};

  REQUIRE(oss.str() == output);

  // // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

// ============== END OF FILE ==============