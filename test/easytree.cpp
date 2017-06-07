#include <catch.hpp>

#include <easytree/tree>
#include <easytree/breadth_first>

SCENARIO("TDD") {
  using namespace easytree;
  WHEN("Non-const tree") {
    auto tree =
      node<int>(1) << node<int>(2)
                   << node<int>(3)
                   << node<int>(4)
                   << (node<int>(5)
                       << node<int>(6)
                       << node<int>(7))
                   << (node<int>(8)
                       << (node<int>(9)
                           << node<int>(10)
                           << node<int>(11))
                       << node<int>(12));

    THEN("Test breadth-first") {
      std::vector<int> actual;
      for (auto& v : breadth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 2, 3, 4, 5, 8, 6, 7, 9, 12, 10, 11};
      REQUIRE(actual == expected);
    }
  }
  
  WHEN("Const tree") {
    const auto tree =
      node<int>(1) << node<int>(2)
                   << node<int>(3)
                   << node<int>(4)
                   << (node<int>(5)
                       << node<int>(6)
                       << node<int>(7))
                   << (node<int>(8)
                       << (node<int>(9)
                           << node<int>(10)
                           << node<int>(11))
                       << node<int>(12));

    THEN("Test breadth-first") {
      std::vector<int> actual;
      for (const auto& v : breadth_first<int>(tree)) {
        actual.push_back(**v);
      }
      std::vector<int> expected{1, 2, 3, 4, 5, 8, 6, 7, 9, 12, 10, 11};
      REQUIRE(actual == expected);
    }
  }
}
