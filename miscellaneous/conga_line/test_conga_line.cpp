#include "../../tests/catch.hpp"
#include "conga_line.hpp"

TEST_CASE("Example 1") {
  std::istringstream iss {"3 6\namelia bubba\nkiryu coco\nollie udin\nPBBPFP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"bubba\ncoco\namelia\n\namelia\nbubba\nkiryu\ncoco\nollie\nudin\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 2") {
  std::istringstream iss {"3 6\namelia bubba\nkiryu coco\nollie udin\nBRBPRFFPRBBBBBRP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"kiryu\nbubba\ncoco\n\nkiryu\nollie\nudin\nbubba\ncoco\namelia\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 3") {
  std::istringstream iss {"3 6\namelia bubba\nkiryu coco\nollie udin\nBRBPRFFPRBBBBBRPCBBCFP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"kiryu\nbubba\ncoco\nollie\n\nollie\nudin\ncoco\nkiryu\namelia\nbubba\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 4") {
  std::istringstream iss {"2 3\namelia bubba\nkiryu coco\nBCP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"coco\n\namelia\nbubba\nkiryu\ncoco\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 5") {
  std::istringstream iss {"1 2\namelia bubba\nCP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"amelia\n\nbubba\namelia\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

TEST_CASE("Example 6") {
  std::istringstream iss {"1 1\namelia bubba\nP\n"};
  std::ostringstream oss {};
  
  // Redirect std::cin and std::cout
  std::streambuf* original_cin = std::cin.rdbuf(iss.rdbuf());
  std::streambuf* original_cout = std::cout.rdbuf(oss.rdbuf());

  main_program();
  std::string output {"bubba\n\namelia\nbubba\n"};
  REQUIRE(oss.str() == output);

  // Restore std::cin and std::cout
  std::cin.rdbuf(original_cin);
  std::cout.rdbuf(original_cout);
}

// ============== END OF FILE ==============
